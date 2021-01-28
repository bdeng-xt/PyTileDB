#pragma once
#ifndef TILEDB_ARRAY_UTIL_H
#define TILEDB_ARRAY_UTIL_H

/**
* \file array_util.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide utility functions for tiledb array.
*
* \description
*	This component provides utility functions for tiledb array.
*/

#include <limits>
#include <codecvt>

#include "array.h"
#include "array_schema.h"
#include "attribute.h"
#include "config.h"
#include "context.h"
#include "deleter.h"
#include "dimension.h"
#include "domain.h"
#include "exception.h"
#include "filter.h"
#include "filter_list.h"
#include "group.h"
#include "object.h"
#include "object_iter.h"
#include "query.h"
#include "schema_base.h"
#include "stats.h"
#include "tiledb.h"
#include "utils.h"
#include "version.h"
#include "vfs.h"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/functional.h"
#include "pybind11/numpy.h"

 
#include <arrow/api.h>
#include <arrow/python/pyarrow.h>

namespace tiledb {

class ArrayUtil {
public:
	/**
	* @name Constructor and Destructor
	*/
	///@{

	/**
	* @brief constructor
	*/
	ArrayUtil() {}

	/**
	* @brief copy constructor
	*/
	ArrayUtil(const tiledb::ArrayUtil& from) {} // = delete;

    /**
	 * @brief copy assignment
	*/
	ArrayUtil& operator=(const tiledb::ArrayUtil& from) { return *this; } // = delete;

	/**
	* @brief destructor
	*/
	virtual ~ArrayUtil() {}

	///@}

protected:
public:
	/**
	* @brief get version
	*
	* @return version string
	*/
	static std::string get_version()
	{
		std::tuple<int, int, int> t = tiledb::version();
		return std::to_string(std::get<0>(t)) + "." + std::to_string(std::get<1>(t)) + "." + std::to_string(std::get<2>(t));
	}//std::string ArrayUtil::get_version()

	//static tiledb::ArraySchema create_array_schema(const tiledb::Context& ctx, py::kwargs kwargs)
	//{
	//	tiledb_array_type_t array_type = tiledb_array_type_t::TILEDB_SPARSE;
	//	//if(kwargs.c)
	//	bool is_dense = false;
	//	if (kwargs.contains<std::string>("dense"))
	//	{
	//		is_dense=(*kwargs["dense"].begin()).cast<bool>();
	//	}
	//	
	//	if (is_dense)
	//	{
	//		array_type = tiledb_array_type_t::TILEDB_DENSE;
	//	}
	//	return tiledb::ArraySchema(ctx, array_type);
	//}//tiledb::ArraySchema ArrayUtil::create_array_schema(const tiledb::Context& ctx, py::kwargs kwargs)

	//static tiledb::ArraySchema open_array_schema(const tiledb::Context& ctx, const std::string& uri)
	//{
	//	return tiledb::ArraySchema(ctx, uri);
	//}//tiledb::ArraySchema ArrayUtil::open_array_schema(const tiledb::Context& ctx, const std::string& uri)

	//static std::shared_ptr<tiledb::Array> create_array(const std::string& uri, const tiledb::ArraySchema& schema, py::kwargs kwargs)
	//{
	//	tiledb::Array::create(uri, schema);
	//	tiledb::Context ctx;
	//	return std::shared_ptr<tiledb::Array>(new tiledb::Array(ctx, uri, tiledb_query_type_t::TILEDB_WRITE));
	//}//tiledb::Array ArrayUtil::create_array(const std::string& uri, const tiledb::ArraySchema& schema, py::kwargs kwargs)


	/*
	* @brief open an array
	*
	* @param uri
	*
	* @return tiledb Array
	*/
	static std::shared_ptr<tiledb::Array> open_array(const tiledb::Context& ctx, const std::string& uri, const std::string& rw)
	{
		if (rw.find("w") != std::string::npos || rw.find("W") != std::string::npos)
		{
			return std::shared_ptr<tiledb::Array>(new tiledb::Array(ctx, uri, tiledb_query_type_t::TILEDB_WRITE));
		}
		else
		{
			return std::shared_ptr<tiledb::Array>(new tiledb::Array(ctx, uri, tiledb_query_type_t::TILEDB_READ));
		}
	}//tiledb::Array ArrayUtil::open_array(const tiledb::Context& ctx, const std::string& uri, const std::string& rw)

	 
	static std::vector<std::string> dimension_names_of_array_schema(const tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		std::vector<tiledb::Dimension> dims = schema.domain().dimensions();
		for (auto it = dims.begin(); it != dims.end(); ++it)
		{
			result.push_back(it->name());
		}
		return result;
	}

	static std::vector<std::string> attribute_names_of_array_schema(const tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		std::unordered_map<std::string, tiledb::Attribute> attrs= schema.attributes();
		for (auto it = attrs.begin(); it != attrs.end(); ++it)
		{
			result.push_back(it->second.name());
		}

		return result;
	}

	static std::vector<std::string> coords_filter_names_of_array_schema(tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		tiledb::FilterList filter_list = schema.coords_filter_list();

		uint32_t n = filter_list.nfilters();
		for (uint32_t i = 0; i < n; ++i)
		{
			tiledb::Filter filter = filter_list.filter(i);
			result.push_back(tiledb::Filter::to_str(filter.filter_type()));
		}

		return result;
	}

	static std::vector<std::string> offsets_filter_names_of_array_schema(tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		tiledb::FilterList filter_list = schema.offsets_filter_list();
		uint32_t n = filter_list.nfilters();
		for (uint32_t i = 0; i < n; ++i)
		{
			tiledb::Filter filter = filter_list.filter(i);
			result.push_back(tiledb::Filter::to_str(filter.filter_type()));
		}

		return result;
	}

	static std::vector<std::string> dimension_filter_names_of_array_schema(const tiledb::ArraySchema& schema, const std::string& name)
	{
		std::vector<std::string> result;

		tiledb::Domain domain = schema.domain();
		if (domain.has_dimension(name))
		{
			tiledb::Dimension dim = domain.dimension(name);
			tiledb::FilterList filter_list = dim.filter_list();
			uint32_t n = filter_list.nfilters();
			for (uint32_t i = 0; i < n; ++i)
			{
				tiledb::Filter filter = filter_list.filter(i);
				result.push_back(tiledb::Filter::to_str(filter.filter_type()));
			}
		}

		return result;
	}

	static std::vector<std::string> attribute_filter_names_of_array_schema(const tiledb::ArraySchema& schema,const std::string& name)
	{
		std::vector<std::string> result;
		if (schema.has_attribute(name))
		{
			tiledb::Attribute attr = schema.attribute(name);
			tiledb::FilterList filter_list = attr.filter_list();
			uint32_t n = filter_list.nfilters();
			for (uint32_t i = 0; i < n; ++i)
			{
				tiledb::Filter filter = filter_list.filter(i);
				result.push_back(tiledb::Filter::to_str(filter.filter_type()));
			}
		}

		return result;
	}

	static tiledb_datatype_t datatype_of_dimension_or_attribute(tiledb::ArraySchema& schema, const std::string& name)
	{
		if (schema.has_attribute(name))
		{
			tiledb::Attribute attr = schema.attribute(name);
			return attr.type();
		}
		else if (schema.domain().has_dimension(name))
		{
			tiledb::Dimension dim = schema.domain().dimension(name);
			return dim.type();
		}
		return tiledb_datatype_t::TILEDB_ANY;
	}

	static void add_coords_filter_to_array_schema(const tiledb::Context& ctx, tiledb::ArraySchema& schema, tiledb_filter_type_t filter_type)
	{
		tiledb::FilterList filter_list = schema.coords_filter_list();
		tiledb::Filter filter(ctx, filter_type);
		filter_list.add_filter(filter);
		schema.set_coords_filter_list(filter_list);

	}//static void add_coords_filter_to_array_schema(tiledb::ArraySchema& schema, tiledb_filter_type_t filter_type)

	static void add_offsets_filter_to_array_schema(const tiledb::Context& ctx, tiledb::ArraySchema& schema, tiledb_filter_type_t filter_type)
	{
		tiledb::FilterList filter_list = schema.offsets_filter_list();
		tiledb::Filter filter(ctx, filter_type);
		filter_list.add_filter(filter);
		schema.set_offsets_filter_list(filter_list);
	}//static void add_offsets_filter_to_array_schema(tiledb::ArraySchema& schema, tiledb_filter_type_t filter_type)

	static void add_dimension_filter_to_array_schema(const tiledb::Context& ctx, tiledb::ArraySchema& schema, const std::string& dim_name, tiledb_filter_type_t filter_type)
	{
		tiledb::Domain domain = schema.domain();
		if (domain.has_dimension(dim_name))
		{
			tiledb::Dimension dim = domain.dimension(dim_name);
			tiledb::FilterList filter_list = dim.filter_list();
			tiledb::Filter filter(ctx, filter_type);
			filter_list.add_filter(filter);
			dim.set_filter_list(filter_list);
			domain.add_dimension(dim);

		}

	}//static void add_dimension_filter_to_array_schema(tiledb::ArraySchema& schema, const std::string& dim_name, tiledb_filter_type_t filter_type)

	static void add_attribute_filter_to_array_schema(const tiledb::Context& ctx, tiledb::ArraySchema& schema, const std::string& attr_name, tiledb_filter_type_t filter_type)
	{
		if (schema.has_attribute(attr_name))
		{
			tiledb::Attribute attr = schema.attribute(attr_name);
			tiledb::FilterList filter_list = attr.filter_list();
			tiledb::Filter filter(ctx, filter_type);
			filter_list.add_filter(filter);
			attr.set_filter_list(filter_list);
			schema.add_attribute(attr);
		}
	}//static void add_attribute_filter_to_array_schema(tiledb::ArraySchema& schema, const std::string& dim_name, tiledb_filter_type_t filter_type)

	static std::string json_str_of_array_schema(const tiledb::ArraySchema& schema)
	{
		std::cout << "start to get json str of schema..." << std::endl;
		std::stringstream ss;
		ss << "{";

		ss << "\"dimensions\":[";
		tiledb::Domain domain = schema.domain();
		std::vector<tiledb::Dimension> dims = domain.dimensions();
		int ndim = (int)dims.size();
		std::cout << "start to get json str of dimenions:" << ndim << std::endl;
		for (int i = 0; i < ndim; ++i)
		{
			if (i > 0) { ss << ","; }
			ss << "{";
			ss << "\"name\":\"" << dims[i].name() << "\"";
			ss << ",\"type\":" << dims[i].type();
			ss << ",\"domain_bound\":\"" << dims[i].domain_to_str() << "\"";
			ss << "}";
		}
		ss << "]";

		ss << ",\"attributes\":[";
		std::cout << "start to get json str of attrs..." << std::endl;
		std::unordered_map<std::string, tiledb::Attribute> attrs = schema.attributes();
		int attr_count = 0;
		for (auto it = attrs.begin(); it != attrs.end(); ++it)
		{
			if (attr_count > 0) { ss << ","; }
			ss << "{";
			ss << "\"name\":\"" << it->second.name() << "\"";
			ss << ",\"dtype\":" << it->second.type();
			ss << "}";

			++attr_count;
		}
		ss << "]";

		ss << ",\"tile_order\":" << schema.tile_order();
		ss << ",\"cell_order\":" << schema.cell_order();



		ss << "}";
		return ss.str();
	}

//	static tiledb::ArraySchema create_array_schema_from_json_str(const std::string& json_str)
//	{
//	}

	static std::shared_ptr<tiledb::Query> make_query(const tiledb::Context& ctx, const std::shared_ptr<tiledb::Array>& arr, tiledb_query_type_t query_type)
	{
		return std::shared_ptr<tiledb::Query>(new Query(ctx, *arr, query_type));
	}

	static void set_int32_buffer_for_query(std::shared_ptr<tiledb::Query>& query, const std::string& name, std::vector<int> buffer)
	{
	//	tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_WRITE);
		query->set_buffer<int>(name, buffer);

	}

	static void set_int64_buffer_for_query(std::shared_ptr<tiledb::Query>& query, const std::string& name, std::vector<int64_t> buffer)
	{
		query->set_buffer<int64_t>(name, buffer);
	}

	static void set_double_buffer_for_query(std::shared_ptr<tiledb::Query>& query, const std::string& name, std::vector<double> buffer)
	{
		query->set_buffer<double>(name, buffer);
	}

	static void set_string_buffer_for_query(std::shared_ptr<tiledb::Query>& query, const std::string& name, std::vector<std::string> buffer)
	{
		std::vector<uint64_t> offsets;
		int n = (int)buffer.size();
		offsets.reserve(n);
		std::string str_data;
		for (int i = 0; i < n; ++i)
		{
			if (i == 0) 
			{
				offsets.push_back(0); 
			}
			else
			{
				offsets.push_back( offsets[i-1] + ((uint64_t)buffer[i - 1].size()) );
			}
			str_data += buffer[i];
		}

		query->set_buffer(name, offsets, str_data);

	}

 
	static std::vector<int> get_int32_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);
		std::vector<int> result(sz/sizeof(int));

		
		query.set_buffer<int>(name, result);
		 
		query.submit();

		arr.close();
		return result;
	}

	static std::vector<uint32_t> get_uint32_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);
		std::vector<uint32_t> result(sz / sizeof(uint32_t));


		query.set_buffer<uint32_t>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	static std::vector<int64_t> get_int64_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);

		std::vector<int64_t> result(sz/sizeof(int64_t));
		query.set_buffer<int64_t>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	static std::vector<uint64_t> get_uint64_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);

		std::vector<uint64_t> result(sz / sizeof(uint64_t));
		query.set_buffer<uint64_t>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	static std::vector<double> get_double_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);

		std::vector<double> result(sz/sizeof(double));
		query.set_buffer<double>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	static std::vector<std::string> get_string_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		std::pair<uint64_t, uint64_t> result_size = query.est_result_size_var(name);
		uint64_t sz = result_size.first;

		std::string str_result;
		str_result.resize(result_size.second);

		std::vector<uint64_t> offsets(sz);

		query.set_buffer(name, offsets, str_result);

		query.submit();

		std::unordered_map<std::string, std::pair<uint64_t, uint64_t>> result_el_map= query.result_buffer_elements();
		uint64_t offsets_sz = result_el_map[name].first;
		std::vector<uint64_t> result_str_sizes;
		result_str_sizes.reserve(offsets_sz);
		for (size_t i = 0; i < (offsets_sz - 1); ++i)
		{
			result_str_sizes.push_back(offsets[i + 1] - offsets[i]);
		}
		uint64_t total_size = result_el_map[name].second * sizeof(char);
		result_str_sizes.push_back(total_size - offsets[offsets.size() - 1]);

		std::vector<std::string> result;
		result.reserve(offsets_sz);
		for (size_t i = 0; i < offsets_sz; ++i)
		{
			
			result.push_back(std::string(&str_result[offsets[i]], result_str_sizes[i]));
		}
		arr.close();
		return result;
	}

	static std::shared_ptr<arrow::Table>  read_to_arrow_talbe(const std::string& uri, const std::vector<std::string>& columns)
	{
	//	std::cout << "start to read from uri:" << uri << std::endl;
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		std::vector<std::shared_ptr<arrow::Field>> fields;

		std::vector<tiledb::Dimension> dims = query.array().schema().domain().dimensions();
		std::unordered_map<std::string, tiledb::Attribute> attrs = query.array().schema().attributes();

		for (auto& dim : dims)
		{
			std::shared_ptr<arrow::KeyValueMetadata> kvmeta = std::shared_ptr<arrow::KeyValueMetadata>(new arrow::KeyValueMetadata());
			kvmeta->Append("isdim", "1");
			std::shared_ptr<arrow::DataType> arrow_data_type = tiledb_datatype_to_arrow(dim.type());
			std::shared_ptr<arrow::Field> field = std::shared_ptr<arrow::Field>(new arrow::Field(dim.name(), arrow_data_type, true, kvmeta));
			if (columns.size() > 0 && std::find(columns.begin(), columns.end(), field->name()) == columns.end())
			{
				continue; //filter out
			}
			
			fields.emplace_back(field);

		}//for (auto& dim : dims)

		for (auto& attr : attrs)
		{
			std::shared_ptr<arrow::KeyValueMetadata> kvmeta = std::shared_ptr<arrow::KeyValueMetadata>(new arrow::KeyValueMetadata());
			kvmeta->Append("isattr", "1");
			std::shared_ptr<arrow::DataType> arrow_data_type = tiledb_datatype_to_arrow(attr.second.type());
			std::shared_ptr<arrow::Field> field = std::shared_ptr<arrow::Field>(new arrow::Field(attr.second.name(), arrow_data_type, true, kvmeta));
			if (columns.size() > 0 && std::find(columns.begin(), columns.end(), field->name()) == columns.end())
			{
				continue; //filter out
			}
			fields.emplace_back(field);
		}//for (auto& attr : attrs)

		std::shared_ptr<arrow::Schema> arrowschema = std::make_shared<arrow::Schema>(fields);
		std::cout << "got arrow_schema:" << arrowschema->ToString() << std::endl;
	 
		//////
		std::vector<std::shared_ptr<arrow::Array>> arrow_arrays;

		int nfileds = arrowschema->num_fields();
		for (int i = 0; i < nfileds; ++i)
		{
			auto field = arrowschema->field(i);


			tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());

			std::shared_ptr<arrow::Array> array;
			switch (tiledb_datatype)
			{
			case tiledb_datatype_t::TILEDB_INT32:
				array = read_int32_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			case tiledb_datatype_t::TILEDB_INT64:
				array = read_int64_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			case tiledb_datatype_t::TILEDB_UINT32:
				array = read_uint32_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			case tiledb_datatype_t::TILEDB_UINT64:
				array = read_uint64_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			case tiledb_datatype_t::TILEDB_FLOAT64:
				array = read_double_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			case tiledb_datatype_t::TILEDB_STRING_ASCII:
			case tiledb_datatype_t::TILEDB_STRING_UTF8:
				array = read_var_size_buffer_to_arrow_array(uri,field->name());
				if (array)
				{
					arrow_arrays.push_back(array);
				}
				break;
			default:
				break;
			}//switch

		}//	for (int i = 0; i < nfileds; ++i)

		std::shared_ptr<arrow::Table> result = arrow::Table::Make(arrowschema, arrow_arrays);

		arr.close();

		return result;
	}//static std::shared_ptr<arrow::Table>  read_to_arrow_talbe(const std::string& uri, const std::vector<std::string>& columns)

	static pybind11::object read_to_pyarrow(const std::string& uri, const std::vector<std::string>& columns)
	{
		std::shared_ptr<arrow::Table> table;
		{
			pybind11::gil_scoped_release scoped_release;
			table = read_to_arrow_talbe(uri, columns);
			if (!table)
			{
				throw pybind11::buffer_error("error in read_to_pyarrow!");
			}
		}

		arrow::py::import_pyarrow();
		return pybind11::reinterpret_steal<pybind11::object>(pybind11::handle(arrow::py::wrap_table(table)));
	}//static pybind11::object read_to_pyarrow(const std::string& uri, const std::vector<std::string>& columns)

	static void write_from_arrow_table(const std::string& uri, const std::shared_ptr<arrow::Table>& table, std::vector<std::string>& dim_columns)
	{
		tiledb::Context ctx;
		ctx.set_tag("sm.check_coord_oob", "false");
		tiledb::VFS vfs(ctx);
		if (vfs.is_dir(uri))
		{
			std::cout << "array_util::write_from_arrow_table, remove old uri:" << uri << std::endl;
			vfs.remove_dir(uri);
		}
		if (!table)
		{
			std::cout << "write_from_arrow_table, null table" << std::endl;
			return;
		}
		std::cout << "write_from_arrow_table, start to write table to:" << uri << std::endl;
		std::vector<std::string> col_names = table->ColumnNames();
		std::cout << "write_from_arrow_table, number of columns:" << col_names.size() 
			<<",number of fields:" << table->fields().size()  << std::endl;
		
		int nfields = (int)table->fields().size();
		int ncols = table->num_columns();
		int64_t nrows = table->num_rows();

		//default compression is gzip with level 6
		tiledb::FilterList filter_list(ctx);
		tiledb::Filter filter(ctx, tiledb_filter_type_t::TILEDB_FILTER_GZIP); 
		int level = 6;
		filter.set_option(tiledb_filter_option_t::TILEDB_COMPRESSION_LEVEL, &level);
		filter_list.add_filter(filter);
	

		tiledb::ArraySchema schema(ctx, tiledb_array_type_t::TILEDB_SPARSE);

		tiledb::Domain domain(ctx);
		
		for (int i=0;i<nfields; ++i) // auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		{
			const std::shared_ptr<arrow::Field>& field = table->field(i);// (*itfield);
			tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());
			
	 
			if ((field->HasMetadata() && field->metadata()->Contains("isdim")
				&& (field->metadata()->Get("isdim").ok()))
				|| (std::find(dim_columns.begin(), dim_columns.end(), field->name()) != dim_columns.end())
				)
			{
				std::string min_str = "";
				std::string max_str = "";
				if (field->HasMetadata())
				{
					auto min_result = field->metadata()->Get("min");
					if (min_result.ok())
					{
						min_str = min_result.ValueUnsafe();
					}

					auto max_result = field->metadata()->Get("max");
					if (max_result.ok())
					{
						max_str = max_result.ValueUnsafe();
					}
				}

				

				if (field->name() == "rows" && min_str.empty() && max_str.empty())
				{
					min_str = "0";
					std::stringstream ssmax;
					ssmax << (nrows-1);
					max_str = ssmax.str();
				}
				
				std::cout << "start to add dimension:" << field->name() << ",min_str:" << min_str
					<< ",max_str:" << max_str << std::endl;

				if (tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS2
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS4
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF16
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF32
					)
				{
					tiledb::Dimension dim = tiledb::Dimension::create(ctx, field->name(), tiledb_datatype_t::TILEDB_STRING_ASCII, nullptr, nullptr);
//					dim.set_cell_val_num(TILEDB_VAR_NUM);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added string dimension:" << field->name() << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT32)
				{
					int extent = 10;
					std::array<int, 2> bound;
					bound[0] = (std::numeric_limits<int>::min()) / extent;
					bound[1] = (std::numeric_limits<int>::max() / extent) - extent;
					if ((!min_str.empty()) && (!max_str.empty()))
					{
						bound[0] = atoi(min_str.c_str());
						bound[1] = atoi(max_str.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<int>(ctx, field->name(), bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added int32 dimension:" << field->name() << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT32)
				{
					uint32_t extent = 10;
					std::array<uint32_t, 2> bound;
					bound[0] = std::numeric_limits<uint32_t>::min() / extent;
					bound[1] = (std::numeric_limits<uint32_t>::max() / extent) - extent;
					if ((!min_str.empty()) && (!max_str.empty()))
					{
						bound[0] = atoi(min_str.c_str());
						bound[1] = atoi(max_str.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<uint32_t>(ctx, field->name(), bound, extent);

					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added uint32 dimension:" << field->name() << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT64)
				{
					int64_t extent = 10;
					std::array<int64_t, 2> bound;
					bound[0] = std::numeric_limits<int64_t>::min() / extent;
					bound[1] = (std::numeric_limits<int64_t>::max() / extent) - extent;
					if ((!min_str.empty()) && (!max_str.empty()))
					{
						bound[0] = atoll(min_str.c_str());
						bound[1] = atoll(max_str.c_str());
					}
					tiledb::Dimension dim = tiledb::Dimension::create<int64_t>(ctx, field->name(), bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added int64 dimension:" << field->name() << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT64)
				{
					uint64_t extent = 10;
					std::array<uint64_t, 2> bound;
					bound[0] = std::numeric_limits<uint64_t>::min() / extent;
					bound[1] = (std::numeric_limits<uint64_t>::max() / extent) - extent;
					if ((!min_str.empty()) && (!max_str.empty()))
					{
						bound[0] = atoll(min_str.c_str());
						bound[1] = atoll(max_str.c_str());
					}
					tiledb::Dimension dim = tiledb::Dimension::create<uint64_t>(ctx, field->name(), bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added uint64 dimension:" << field->name() << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_FLOAT64)
				{
					double extent = 10;
					std::array<double, 2> bound;
					bound[0] = int64_t(std::numeric_limits<double>::min() / extent);
					bound[1] = int64_t((std::numeric_limits<double>::max() / extent) - extent);
					if ((!min_str.empty()) && (!max_str.empty()))
					{
						bound[0] = atof(min_str.c_str());
						bound[1] = atof(max_str.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<double>(ctx, field->name(), bound, 10);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added float64 dimension:" << field->name() << std::endl;
				}
				else
				{
					std::cout << "not implemented type:" << tiledb_datatype << ", for field:" << field->name() << std::endl;
				}

			}//if
			 
		}//for (auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		std::cout << "start to check dimension..." << std::endl;
		bool added_dim_rows = false;
		if (domain.ndim() == 0)
		{
			uint64_t extent = 10;
			std::array<uint64_t, 2> bound;
			bound[0] = 0;
			bound[1] = table->num_rows()-1;// (std::numeric_limits<uint64_t>::max() / extent) - extent; // // ;

			tiledb::Dimension dim = tiledb::Dimension::create<uint64_t>(ctx, "rows", bound, extent);
			dim.set_filter_list(filter_list);
			domain.add_dimension(dim);
			added_dim_rows=true;
		}
//		std::cout << "start to set domain..." << std::endl;

		schema.set_domain(domain);
		schema.set_cell_order(TILEDB_ROW_MAJOR);
		schema.set_tile_order(TILEDB_ROW_MAJOR);
		
		//now start to add attribute
		for (int i=0;i<nfields; ++i) // auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		{
			const std::shared_ptr<arrow::Field>& field = table->field(i);// (*itfield);
			tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());
			if (domain.has_dimension(field->name()))
			{
				continue;//ignore dimension column
			}

	 		
			
			//attr.set_filter_list()
			if (tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS2
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS4
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF16
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF32
				)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<std::string>(ctx, field->name());//  //attr(ctx, field->name(), tiledb_datatype);
//				attr.set_cell_val_num(TILEDB_VAR_NUM);
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added string attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT32)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<int>(ctx, field->name());
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added int attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT64)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<int64_t>(ctx, field->name());
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added int64 attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT32)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<uint32_t>(ctx, field->name());
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added uint32_t attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT64)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<uint64_t>(ctx, field->name());
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added uint64_t attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_FLOAT64)
			{
				tiledb::Attribute attr = tiledb::Attribute::create<double>(ctx, field->name());
				attr.set_filter_list(filter_list);
				schema.add_attribute(attr);
				std::cout << "added double attribute:" << field->name() << ",datatype:" << tiledb_datatype << std::endl;
			}
			else
			{
				std::cout << "not implemented type:" << tiledb_datatype << ", for field:" << field->name() << std::endl;
			}

		}//for (auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)



		std::cout << "start to create array:" << uri << ",schema:" << schema.to_info_str() << std::endl;
		tiledb::Array::create(uri, schema); //create array

		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_WRITE);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_WRITE);
		query.set_layout(tiledb_layout_t::TILEDB_UNORDERED);

		std::unordered_map<std::string, std::vector<int64_t> > int64_vector_map;
		std::unordered_map<std::string, std::vector<int> > int32_vector_map;
		std::unordered_map<std::string, std::vector<uint64_t> > uint64_vector_map;
		std::unordered_map<std::string, std::vector<uint32_t> > uint32_vector_map;
		std::unordered_map<std::string, std::vector<double> > double_vector_map;

		std::unordered_map<std::string, std::string > string_buffer_map;
		std::unordered_map<std::string, std::vector<uint64_t> > string_buffer_offset_map;
 
		if (added_dim_rows)
		{
			uint64_vector_map["rows"] = std::vector<uint64_t>();
			auto& data_rows = uint64_vector_map["rows"];
			data_rows.reserve(table->num_rows());
			for (int i = 0; i < table->num_rows(); ++i)
			{
				data_rows.push_back(i);
			}
			std::cout << "start to set uint64 field:rows,num_rows:" << table->num_rows() << std::endl;
			query.set_uint64_vector_buffer("rows", data_rows);
		}

		for (int i = 0; i < nfields; ++i) //(auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		{
			const std::shared_ptr<arrow::Field>& field = table->field(i);// (*itfield);
			std::shared_ptr<arrow::DataType> arrow_datatype = field->type();
			tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());
			
			auto arrow_arr = table->GetColumnByName(field->name());
		
			if (arrow_datatype->id() == arrow::Type::STRING)
			{
				string_buffer_map[field->name()] = "";
				string_buffer_offset_map[field->name()] = std::vector<uint64_t>();

				std::string& data = string_buffer_map[field->name()];
				std::vector<uint64_t>& offsets = string_buffer_offset_map[field->name()];

				int status = get_data_offsets_for_arrow_table_string_field(table, i, data, offsets);
				if (status != 0)
				{
					std::cout << "failed to get data buffer for tiledb from arrow table!" << std::endl;
					continue;
				}

	
				std::cout << "start to set string field:" << field->name()  <<",datasize:" << data.size() << std::endl;
  
				query.set_buffer(field->name(), offsets, data);
				 
				
			}
			else if (arrow_datatype->id() == arrow::Type::INT32)
			{
				int32_vector_map[field->name()] = std::vector<int>();
				std::vector<int>& data = int32_vector_map[field->name()];
				data.reserve(table->num_rows());
				for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
				{
					auto arrow_array = std::static_pointer_cast<arrow::Int32Array>(*itchunk);
					for (int64_t i = 0; i < arrow_array->length(); ++i)
					{
						data.push_back(arrow_array->Value(i));
					}
				}
				std::cout << "start to set int32 field:" << field->name()  << ",datasize:" << data.size() << std::endl;
				query.set_int32_vector_buffer(field->name(), data);
			}
			else if (arrow_datatype->id() == arrow::Type::UINT32)
			{
				uint32_vector_map[field->name()] = std::vector<uint32_t>();
				std::vector<uint32_t>& data = uint32_vector_map[field->name()];
				data.reserve(table->num_rows());
				for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
				{
					auto arrow_array = std::static_pointer_cast<arrow::UInt32Array>(*itchunk);
					for (int64_t i = 0; i < arrow_array->length(); ++i)
					{
						data.push_back(arrow_array->Value(i));
					}
				}
				std::cout << "start to set uint32 field:" << field->name()  << ",datasize:" << data.size() << std::endl;
				query.set_uint32_vector_buffer(field->name(), data);
			}
			else if (arrow_datatype->id() == arrow::Type::INT64)
			{
				int64_vector_map[field->name()] = std::vector<int64_t>();
				std::vector<int64_t>& data = int64_vector_map[field->name()];
				data.reserve(table->num_rows());
				for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
				{
					auto arrow_array = std::static_pointer_cast<arrow::Int64Array>(*itchunk);
					for (int64_t i = 0; i < arrow_array->length(); ++i)
					{
						data.push_back(arrow_array->Value(i));
					}
				}
				std::cout << "start to set int64 field:" << field->name()  << ",datasize:" << data.size() << std::endl;
				query.set_int64_vector_buffer(field->name(), data);
			}
			else if (arrow_datatype->id() == arrow::Type::UINT64)
			{
				uint64_vector_map[field->name()] = std::vector<uint64_t>();
				std::vector<uint64_t>& data = uint64_vector_map[field->name()];
				data.reserve(table->num_rows());
				for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
				{
					auto arrow_array = std::static_pointer_cast<arrow::UInt64Array>(*itchunk);
					for (int64_t i = 0; i < arrow_array->length(); ++i)
					{
						data.push_back(arrow_array->Value(i));
					}
				}
				std::cout << "start to set uint64 field:" << field->name() << ",datasize:" << data.size() << std::endl;
				query.set_uint64_vector_buffer(field->name(), data);
			}
			else if (arrow_datatype->id() == arrow::Type::DOUBLE)
			{
				double_vector_map[field->name()] = std::vector<double>();
				std::vector<double>& data = double_vector_map[field->name()];
				data.reserve(table->num_rows());
				for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
				{
					auto arrow_array = std::static_pointer_cast<arrow::DoubleArray>(*itchunk);
					for (int64_t i = 0; i < arrow_array->length(); ++i)
					{
						data.push_back(arrow_array->Value(i));
					}
				}
				std::cout << "start to set double field:" << field->name()  << ",datasize:" << data.size() << std::endl;
				query.set_double_vector_buffer(field->name(), data);
			}
			else
			{
				std::cout << "not implemented type:" << arrow_datatype->id() << std::endl;
			}



		}//for (auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		std::cout << "query start to submit" << std::endl;
		tiledb::Query::Status status = query.submit();
		std::cout << "query submitted:" << status << std::endl;

		query.finalize();
		arr.close();


	}//static void write_from_arrow_table

	static void write_from_pyarrow(const std::string& uri, pybind11::object& pyobj, std::vector<std::string>& dim_columns)
	{
		arrow::py::import_pyarrow();
		if (pyobj.is_none())
		{
			std::cout << "write_from_pyarrow, pyobj is None" << std::endl;
			return;
		}
		
	//	std::cout << "start to unwrap_table for pyobj..." << std::endl;
		auto result = arrow::py::unwrap_table(pyobj.ptr());
		
		if (!result.status().ok())
		{
			std::cout << "failed to unwrap_table,status:" << result.status() << std::endl;
		}
		else
		{
			std::cout << "finished unwrap_table, status:" << result.status() << std::endl;
		}

		{
			pybind11::gil_scoped_release scoped_release;

			std::shared_ptr<arrow::Table> table = result.ValueOrDie();

			write_from_arrow_table(uri, table, dim_columns);
		}

	}//static void write_from_pyarrow



protected:
	static int get_data_offsets_for_arrow_table_string_field(const std::shared_ptr<arrow::Table> & table, int i, std::string& data, std::vector<uint64_t>& offsets)
	{
		if (!table)
		{
			//null pointer
			return -1;
		}
		if (i < 0 || i >= table->fields().size())
		{
			//out of range
			return -1;
		}

		const std::shared_ptr<arrow::Field>& field = table->field(i);// (*itfield);
		std::shared_ptr<arrow::DataType> arrow_datatype = field->type();
		if (arrow_datatype->id() != arrow::Type::STRING)
		{
			//not correct type
			return -1;
		}

		tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());
		auto arrow_arr = table->GetColumnByName(field->name());

		data = "";
		offsets.clear();
		data.reserve(table->num_rows());
		offsets.reserve(table->num_rows());
		int count = 0;
		uint64_t offset = 0;
		for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
		{
			auto arrow_array = std::static_pointer_cast<arrow::StringArray>(*itchunk);
			for (int64_t i = 0; i < arrow_array->length(); ++i)
			{
				std::string s = arrow_array->GetString(i);
				data += s;
				offsets.push_back(offset);
				offset += s.size();
			}
			++count;
		}

		return 0;
	}//static int get_data_offsets_for_arrow_table_string_field(const std::shared_ptr<arrow::Table> & table, int i, std::string& data, std::vector<uint64_t>& offsets)
	static int get_data_offsets_for_string_vector(const std::vector<std::string>& buffer, std::string& data, std::vector<uint64_t>& offsets)
	{
	 
		int n = (int)buffer.size();
		offsets.clear();
		offsets.reserve(n);
		data = "";
		data.reserve(n);
	 
		for (int i = 0; i < n; ++i)
		{
			if (i == 0)
			{
				offsets.push_back(0);
			}
			else
			{
				offsets.push_back(offsets[i - 1] + ((uint64_t)buffer[i - 1].size()));
			}
			data += buffer[i];
		}
		return 0;
	}

	static tiledb_datatype_t arrow_datatype_to_tiledb(const std::shared_ptr<arrow::DataType> & data_type)
	{
		//TODO: add more datatype mapping
		switch (data_type->id())
		{
		case arrow::Type::STRING:
			return tiledb_datatype_t::TILEDB_STRING_ASCII;//  TILEDB_STRING_UTF8;
		case arrow::Type::INT32:
			return tiledb_datatype_t::TILEDB_INT32;
		case arrow::Type::INT64:
			return tiledb_datatype_t::TILEDB_INT64;
		case arrow::Type::UINT32:
			return tiledb_datatype_t::TILEDB_UINT32;
		case arrow::Type::UINT64:
			return tiledb_datatype_t::TILEDB_UINT64;
		case arrow::Type::DOUBLE:
			return tiledb_datatype_t::TILEDB_FLOAT64;
		default:
			return tiledb_datatype_t::TILEDB_ANY;

		}
	}

	static std::shared_ptr<arrow::DataType> tiledb_datatype_to_arrow(tiledb_datatype_t data_type) {
		//TODO: add more datatype mapping
		switch (data_type)
		{
		case tiledb_datatype_t::TILEDB_ANY:
			return std::make_shared<arrow::StringType>();
		case tiledb_datatype_t::TILEDB_INT32:
			return arrow::int32();
		case tiledb_datatype_t::TILEDB_INT64:
			return arrow::int64();
		case tiledb_datatype_t::TILEDB_UINT32:
			return arrow::uint32();
		case tiledb_datatype_t::TILEDB_UINT64:
			return arrow::uint64();
		case tiledb_datatype_t::TILEDB_FLOAT64:
			return arrow::float64();
		case tiledb_datatype_t::TILEDB_STRING_ASCII:
			return std::make_shared<arrow::StringType>();
		case tiledb_datatype_t::TILEDB_STRING_UTF8:
			return std::make_shared<arrow::StringType>();
		case tiledb_datatype_t::TILEDB_DATETIME_US:
			return arrow::timestamp(arrow::TimeUnit::MICRO);
		default:
			return std::make_shared<arrow::StringType>();

		}
	}

//	static std::shared_ptr<arrow::Array> read_int32_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_int32_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		uint64_t sz = query.est_result_size(name);
		std::vector<int> result(sz / sizeof(int));
		query.set_buffer<int>(name, result);
		query.submit();

		arrow::Int32Builder builder;
		builder.Resize(sz / sizeof(int));
		builder.AppendValues(result);
		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);

		return (status == arrow::Status::OK()) ? array : std::shared_ptr<arrow::Array>(nullptr);
	}// 

	//static std::shared_ptr<arrow::Array> read_int64_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_int64_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		uint64_t sz = query.est_result_size(name);
		std::vector<int64_t> result(sz / sizeof(int64_t));
		query.set_buffer<int64_t>(name, result);
		query.submit();
		arr.close();

		arrow::Int64Builder builder;
		builder.Resize(sz / sizeof(int64_t));
		builder.AppendValues(result);
		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);

		return (status == arrow::Status::OK()) ? array : std::shared_ptr<arrow::Array>(nullptr);
	}// 

	//static std::shared_ptr<arrow::Array> read_uint32_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_uint32_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		uint64_t sz = query.est_result_size(name);
		std::vector<uint32_t> result(sz / sizeof(uint32_t));
		query.set_buffer<uint32_t>(name, result);
		query.submit();
		arr.close();

		arrow::UInt32Builder builder;
		builder.Resize(sz / sizeof(uint32_t));
		builder.AppendValues(result);
		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);

		return (status == arrow::Status::OK()) ? array : std::shared_ptr<arrow::Array>(nullptr);
	}// 

	//static std::shared_ptr<arrow::Array> read_uint64_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_uint64_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		uint64_t sz = query.est_result_size(name);
		std::vector<uint64_t> result(sz / sizeof(uint64_t));
		query.set_buffer<uint64_t>(name, result);
		query.submit();

		arrow::UInt64Builder builder;
		builder.Resize(sz / sizeof(uint64_t));
		builder.AppendValues(result);
		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);

		return (status == arrow::Status::OK()) ? array : std::shared_ptr<arrow::Array>(nullptr);
	}// 

	//static std::shared_ptr<arrow::Array> read_double_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_double_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		uint64_t sz = query.est_result_size(name);
		std::vector<double> result(sz / sizeof(double));
		query.set_buffer<double>(name, result);
		query.submit();

		arrow::DoubleBuilder builder;
		builder.Resize(sz / sizeof(double));
		builder.AppendValues(result);
		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);

		return (status == arrow::Status::OK()) ? array : std::shared_ptr<arrow::Array>(nullptr);
	}// 

	//static std::shared_ptr<arrow::Array> read_var_size_buffer_to_arrow_array(tiledb::Query& query, const std::string& name)
	static std::shared_ptr<arrow::Array> read_var_size_buffer_to_arrow_array(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

		std::pair<uint64_t, uint64_t> result_size = query.est_result_size_var(name);
		uint64_t sz = result_size.first;

		std::string str_result;
		str_result.resize(result_size.second);

		std::vector<uint64_t> offsets(sz);

		query.set_buffer(name, offsets, str_result);

		query.submit();

		std::unordered_map<std::string, std::pair<uint64_t, uint64_t>> result_el_map = query.result_buffer_elements();
		uint64_t offsets_sz = result_el_map[name].first;
		std::vector<uint64_t> result_str_sizes;
		result_str_sizes.reserve(offsets_sz);
		for (size_t i = 0; i < (offsets_sz - 1); ++i)
		{
			result_str_sizes.push_back(offsets[i + 1] - offsets[i]);
		}
		uint64_t total_size = result_el_map[name].second * sizeof(char);
		result_str_sizes.push_back(total_size - offsets[offsets.size() - 1]);

		std::vector<std::string> result;
		result.reserve(offsets_sz);
		for (size_t i = 0; i < offsets_sz; ++i)
		{
			result.push_back(std::string(&str_result[offsets[i]], result_str_sizes[i]));
		}
		//////
		arrow::StringBuilder builder;
		builder.Resize(offsets_sz);
		builder.AppendValues(result);

		std::shared_ptr<arrow::Array> array;
		arrow::Status status = builder.Finish(&array);
		return array;

	}


};//class ArrayUtil


 

 


}//namespace 

#endif
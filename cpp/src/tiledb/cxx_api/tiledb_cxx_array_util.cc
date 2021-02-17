#include "tiledb_cxx_array_util.h"
#include "tiledb_cxx_json.hpp"
#include "tiledb_cxx_string_util.h"

namespace tiledb {

	std::string ArrayUtil::get_version()
	{
		std::tuple<int, int, int> t = tiledb::version();
		return std::to_string(std::get<0>(t)) + "." + std::to_string(std::get<1>(t)) + "." + std::to_string(std::get<2>(t));
	}//std::string ArrayUtil::get_version()



	std::vector<std::string> ArrayUtil::dimension_names_of_array_schema(const tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		std::vector<tiledb::Dimension> dims = schema.domain().dimensions();
		for (auto it = dims.begin(); it != dims.end(); ++it)
		{
			result.push_back(it->name());
		}
		return result;
	}

	std::vector<std::string> ArrayUtil::attribute_names_of_array_schema(const tiledb::ArraySchema& schema)
	{
		std::vector<std::string> result;

		std::unordered_map<std::string, tiledb::Attribute> attrs = schema.attributes();
		for (auto it = attrs.begin(); it != attrs.end(); ++it)
		{
			result.push_back(it->second.name());
		}

		return result;
	}

	std::vector<std::string> ArrayUtil::coords_filter_names_of_array_schema(tiledb::ArraySchema& schema)
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

	std::vector<std::string> ArrayUtil::offsets_filter_names_of_array_schema(tiledb::ArraySchema& schema)
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

	std::vector<std::string> ArrayUtil::dimension_filter_names_of_array_schema(const tiledb::ArraySchema& schema, const std::string& name)
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

	std::vector<std::string> ArrayUtil::attribute_filter_names_of_array_schema(const tiledb::ArraySchema& schema, const std::string& name)
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

	tiledb_datatype_t ArrayUtil::datatype_of_dimension_or_attribute(tiledb::ArraySchema& schema, const std::string& name)
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

	std::string ArrayUtil::json_str_of_array_schema(const tiledb::ArraySchema& schema)
	{
	//	std::cout << "start to get json str of schema..." << std::endl;
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
			ss << ",\"type\":" << it->second.type();
			ss << "}";

			++attr_count;
		}
		ss << "]";

		ss << ",\"tile_order\":" << schema.tile_order();
		ss << ",\"cell_order\":" << schema.cell_order();



		ss << "}";
		return ss.str();
	}

	tiledb::ArraySchema ArrayUtil::json_str_to_array_schema(const std::string& json_str)
	{
		tiledb::Context ctx;
		tiledb_array_type_t arraytype = tiledb_array_type_t::TILEDB_SPARSE;
		if (!json::json::accept(json_str))
		{
			return tiledb::ArraySchema(ctx, arraytype);
		}

		json::json j;
		j = json::json::parse(json_str);

		if (j.find("dense") != j.end() && j["dense"].get<int>() == 1)
		{
			arraytype = tiledb_array_type_t::TILEDB_DENSE;
		}

		tiledb::ArraySchema schema(ctx, arraytype);

		tiledb::Domain domain(ctx);

		if (j.find("dimensions") != j.end() && j["dimensions"].is_array())
		{
			for (auto& dim_json : j["dimension"])
			{
				if (dim_json.find("name") != dim_json.end() && dim_json.find("type") != dim_json.end())
				{
					std::string name = dim_json["name"].get<std::string>();
					int intdatatype = dim_json["type"].get<int>();
					if (!tiledb::Dimension::is_valid_intdatatype(intdatatype))
					{
						std::cout << "ArrayUtil::json_str_to_array_schema, ignore invalid dimension datatype:" << intdatatype << std::endl;
						continue;
					}
					std::string lower_bound_str = "";
					std::string upper_bound_str = "";
					std::string extent_str = "";
					if (dim_json.find("lower_bound") != dim_json.end())
					{
						lower_bound_str = dim_json["lower_bound"].get<std::string>();
					}
					if (dim_json.find("uppper_bound") != dim_json.end())
					{
						upper_bound_str = dim_json["upper_bound"].get<std::string>();
					}
					if (dim_json.find("extent") != dim_json.end())
					{
						extent_str = dim_json["extent"].get<std::string>();
					}
					tiledb::Dimension dim = tiledb::Dimension::create_dimension(ctx, name, intdatatype, lower_bound_str, upper_bound_str, extent_str);
					domain.add_dimension(dim);

				}
			}
		}//dimensions

		schema.set_domain(domain);


		if (j.find("attributes") != j.end() && j["attributes"].is_array())
		{
			for (auto& attr_json : j["attributes"])
			{
				if (attr_json.find("name") != attr_json.end() && attr_json.find("type") != attr_json.end())
				{
					std::string name = attr_json["name"].get<std::string>();
					int intdatatype = attr_json["type"].get<int>();
					if (!tiledb::Attribute::is_valid_intdatatype(intdatatype))
					{
						std::cout << "ArrayUtil::json_str_to_array_schema, ignore invalid attribute datatype:" << intdatatype << std::endl;
						continue;
					}
					tiledb_datatype_t datatype = (tiledb_datatype_t)intdatatype;
					tiledb::Attribute attr = tiledb::Attribute::create_attribute(ctx, name, datatype);
					schema.add_attribute(attr);
				}//

			}//for (auto& attr_json : j["attributes"])
		}//attributes

		tiledb_layout_t tile_order = tiledb_layout_t::TILEDB_ROW_MAJOR;
		if (j.find("tile_order") != j.end())
		{
			int tile_order_int = j["tile_order"].get<int>();
			if (tile_order_int == (int)tiledb_layout_t::TILEDB_COL_MAJOR)
			{
				tile_order = (tiledb_layout_t::TILEDB_COL_MAJOR);
			}
		}
		schema.set_tile_order(tile_order);

		tiledb_layout_t cell_order = tiledb_layout_t::TILEDB_ROW_MAJOR;
		if (j.find("cell_order") != j.end())
		{
			int cell_order_int = j["cell_order"].get<int>();
			if (cell_order_int == (int)tiledb_layout_t::TILEDB_ROW_MAJOR)
			{
				cell_order = tiledb_layout_t::TILEDB_COL_MAJOR;
			}
		}
		schema.set_cell_order(cell_order);
 

		return schema;
	}


	std::vector<int> ArrayUtil::get_int32_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);
		std::vector<int> result(sz / sizeof(int));


		query.set_buffer<int>(name, result);

		query.submit();

		arr.close();
		return result;
	}

	std::vector<uint32_t> ArrayUtil::get_uint32_vector_from_uri(const std::string& uri, const std::string& name)
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

	std::vector<int64_t> ArrayUtil::get_int64_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);

		std::vector<int64_t> result(sz / sizeof(int64_t));
		query.set_buffer<int64_t>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	std::vector<uint64_t> ArrayUtil::get_uint64_vector_from_uri(const std::string& uri, const std::string& name)
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

	std::vector<double> ArrayUtil::get_double_vector_from_uri(const std::string& uri, const std::string& name)
	{
		tiledb::Context ctx;
		tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);

		tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);
		uint64_t sz = query.est_result_size(name);

		std::vector<double> result(sz / sizeof(double));
		query.set_buffer<double>(name, result);

		query.submit();
		arr.close();
		return result;
	}

	std::vector<std::string> ArrayUtil::get_string_vector_from_uri(const std::string& uri, const std::string& name)
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
		arr.close();
		return result;
	}

	std::shared_ptr<arrow::Table>  ArrayUtil::read_to_arrow_talbe(const std::string& uri, const std::string& json_str)
	{
		std::shared_ptr<tiledb::ColumnDataMap> datamap = read_to_columndatamap(uri, json_str);

		return get_arrow_table_from_columndatamap(datamap);
 
	}//static std::shared_ptr<arrow::Table>  read_to_arrow_talbe 

	pybind11::object ArrayUtil::read_to_pyarrow(const std::string& uri, const std::string& json_str)
	{
		std::shared_ptr<arrow::Table> table;
		{
			pybind11::gil_scoped_release scoped_release;
			table = read_to_arrow_talbe(uri, json_str);
			if (!table)
			{
				throw pybind11::buffer_error("error in read_to_pyarrow!");
			}
		}

		arrow::py::import_pyarrow();
		return pybind11::reinterpret_steal<pybind11::object>(pybind11::handle(arrow::py::wrap_table(table)));
	}//static pybind11::object read_to_pyarrow(const std::string& uri, const std::vector<std::string>& columns)

	std::shared_ptr<tiledb::ColumnDataMap> ArrayUtil::read_to_columndatamap(const std::string& uri, const std::string& query_str)
	{
		std::shared_ptr<tiledb::ColumnDataMap> datamap = std::shared_ptr<tiledb::ColumnDataMap>(new tiledb::ColumnDataMap());

		//	std::cout << "start to read from uri:" << uri << std::endl;
		tiledb::Context ctx;

		try {
			//query json
			json::json j;
			if (json::json::accept(query_str)) //check if it is a valid json string
			{
				j = json::json::parse(query_str);
			}
 
			std::vector<std::string> columns; //default empty columns
			if (j.find("columns") != j.end() && j["columns"].is_array())
			{
				columns = j["columns"].get<std::vector<std::string>>();  //columns = j["columns"].get_to(columns); // 
			}

			tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_READ);
			tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_READ);

			std::vector<tiledb::Dimension> dims = query.array().schema().domain().dimensions();
			std::unordered_map<std::string, tiledb::Attribute> attrs = query.array().schema().attributes();

			for (auto& dim : dims)
			{
				if (columns.size() > 0 && std::find(columns.begin(), columns.end(), dim.name()) == columns.end())
				{
					continue; //filter out
				}
				tiledb_datatype_t dim_datatype = dim.type();
				datamap->add_data_column(dim.name(), dim_datatype);
				if (datamap->has_column(dim.name()))
				{
					datamap->columns()[dim.name()]->set_is_dim(true);
					if (dim_datatype != tiledb_datatype_t::TILEDB_CHAR
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_ASCII
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_UCS2
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_UCS4
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_UTF16
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_UTF32
						&& dim_datatype != tiledb_datatype_t::TILEDB_STRING_UTF8
						&& dim_datatype != tiledb_datatype_t::TILEDB_ANY
						)
					{
						std::string domain_str = dim.domain_to_str();
						StringUtil::replaceAll(domain_str, "[", "");
						StringUtil::replaceAll(domain_str, "]", "");
						std::vector<std::string> bound_items = StringUtil::split(domain_str, ",");
						if (bound_items.size() == 2)
						{
							datamap->columns()[dim.name()]->set_lower_bound(bound_items[0]);
							datamap->columns()[dim.name()]->set_upper_bound(bound_items[1]);
						}
					}
				}
			}//for (auto& dim : dims)

			for (auto& attr : attrs)
			{
				if (columns.size() > 0 && std::find(columns.begin(), columns.end(), attr.second.name()) == columns.end())
				{
					continue; //filter out
				}
				datamap->add_data_column(attr.second.name(), attr.second.type());
			}

			for (auto& column : datamap->columns())
			{
				tiledb_datatype_t datatype = column.second->datatype();
				if (datatype == tiledb_datatype_t::TILEDB_INT32
					|| datatype == tiledb_datatype_t::TILEDB_UINT32
					|| datatype == tiledb_datatype_t::TILEDB_INT64
					|| datatype == tiledb_datatype_t::TILEDB_UINT64
					|| datatype == tiledb_datatype_t::TILEDB_FLOAT64
					)
				{
					uint64_t sz = 0;
					ctx.handle_error(tiledb_query_get_est_result_size(
						ctx.ptr().get(), query.ptr().get(), column.second->name().c_str(), &sz));
					uint64_t data_nelements = uint64_t(sz / column.second->data_element_size());
					column.second->resize_vector(data_nelements);
					column.second->set_buffer();
					
					ctx.handle_error(tiledb_query_set_buffer(
						ctx.ptr().get(),
						query.ptr().get(),
						column.second->name().c_str(),
						column.second->data(), //buff,
						&(column.second->data_bytes_size())));


				}
				else if (datatype == tiledb_datatype_t::TILEDB_CHAR || datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
					|| datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
					)
				{
					std::pair<uint64_t, uint64_t> result_size = query.est_result_size_var(column.second->name());
					uint64_t sz = result_size.first;
					uint64_t sz_bytes = result_size.second;

					column.second->resize_vector(sz);
					column.second->resize_bytes_vector(sz_bytes);

					column.second->set_buffer();

					ctx.handle_error(tiledb_query_set_buffer_var(
						ctx.ptr().get(),
						query.ptr().get(),
						column.second->name().c_str(),
						column.second->offsets(),
						&(column.second->offset_bytes_size()),
						column.second->data(),
						&(column.second->data_bytes_size())
						));
				}
				else
				{
					std::cout << "ArrayUtil::read_from_uri, NOT implemented datatype:" << datatype << ",uri:" << uri << ", with query_str:" << query_str << std::endl;
				}
			}//for (auto& column : datamap->columns())

			//submit
			ctx.handle_error(tiledb_query_submit(ctx.ptr().get(), query.ptr().get()));

			tiledb_query_status_t query_status;
			ctx.handle_error(
				tiledb_query_get_status(ctx.ptr().get(), query.ptr().get(), &query_status));

			if (query_status != tiledb_query_status_t::TILEDB_COMPLETED)
			{
				std::cout << "ArrayUtil::read_from_uri, NOT completed query_status:" << query_status << ",uri:" << uri << ", with query_str:" << query_str << std::endl;
			}
			else
			{
				//read buffer data to vector
				for (auto& column : datamap->columns())
				{
					column.second->read_buffer();
				}
			}

			arr.close();
		}
		catch (tiledb::TileDBError& tdberror)
		{
			std::cout << "ArrayUtil::read_to_columndatamap, got error:" << tdberror.what() <<",uri:" << uri << ", with query_str:" << query_str << std::endl;
			 
		}
		catch (...)
		{
			std::cout << "ArrayUtil::read_to_columndatamap, got unknown error!" << ",uri:" << uri << ", with query_str:" << query_str << std::endl;
		}


		
		
		return datamap;

	}//std::shared_ptr<tiledb::ColumnDataMap> ArrayUtil::read_from_uri

	void ArrayUtil::write_from_columndatamap(const std::string& uri, const std::shared_ptr<tiledb::ColumnDataMap>& datamap, const std::string& json_str)
	{
		json::json j;
		if (json::json::accept(json_str))
		{
			j = json::json::parse(json_str);
		}

		if (!datamap)
		{
			std::cout << "ArrayUtil::write_from_columndatamap, null datamap!" << std::endl;
			return;
		}

		try
		{
			tiledb::Context ctx;
			ctx.set_tag("sm.check_coord_oob", "false");
			tiledb::VFS vfs(ctx);
			if (vfs.is_dir(uri))
			{
				std::cout << "array_util::write_from_columndatamap, remove old uri:" << uri << std::endl;
				vfs.remove_dir(uri);
			}

			//default compression is gzip with level 6
			tiledb::FilterList filter_list(ctx);
			tiledb::Filter filter(ctx, tiledb_filter_type_t::TILEDB_FILTER_GZIP);
			int level = 6;
			filter.set_option(tiledb_filter_option_t::TILEDB_COMPRESSION_LEVEL, &level);
			filter_list.add_filter(filter);

			tiledb_array_type_t arraytype = tiledb_array_type_t::TILEDB_SPARSE;
			if (j.find("dense") != j.end() && j["dense"].is_number_integer())
			{
				if (j["dense"].get<int>() == 1)
				{
					arraytype = tiledb_array_type_t::TILEDB_DENSE;
				}
			}
			tiledb::ArraySchema schema(ctx, arraytype);

			tiledb::Domain domain(ctx);

			std::vector<std::string> dim_names = datamap->dimension_names();
			if (dim_names.size() == 0)
			{
				std::cout << "array_util::write_from_columndatamap, no dimension defined in datamap, uri:" << uri << std::endl;
				return;
			}
			for (auto& dim_name : dim_names)
			{
				if (!datamap->has_column(dim_name))
				{
					continue;//ignore
				}
				std::shared_ptr<tiledb::ColumnData> column = datamap->columns()[dim_name];
				std::string lower_bound = column->lower_bound();
				std::string upper_bound = column->upper_bound();
				tiledb_datatype_t tiledb_datatype = column->datatype();
				if (tiledb_datatype == tiledb_datatype_t::TILEDB_CHAR
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS2
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS4
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF16
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF32
					)
				{
					tiledb::Dimension dim = tiledb::Dimension::create(ctx, dim_name, tiledb_datatype_t::TILEDB_STRING_ASCII, nullptr, nullptr);
					//					dim.set_cell_val_num(TILEDB_VAR_NUM);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added string dimension:" << dim_name << std::endl;

				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT32)
				{
					int extent = 10;
					std::array<int, 2> bound;
					bound[0] = (std::numeric_limits<int>::min()) / extent;
					bound[1] = (std::numeric_limits<int>::max() / extent) - extent;
					if ((!lower_bound.empty()) && (!upper_bound.empty()))
					{
						bound[0] = atoi(lower_bound.c_str());
						bound[1] = atoi(upper_bound.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<int>(ctx, dim_name, bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added int32 dimension:" << dim_name << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT32)
				{
					uint32_t extent = 10;
					std::array<uint32_t, 2> bound;
					bound[0] = std::numeric_limits<uint32_t>::min() / extent;
					bound[1] = (std::numeric_limits<uint32_t>::max() / extent) - extent;
					if ((!lower_bound.empty()) && (!upper_bound.empty()))
					{
						bound[0] = atoi(lower_bound.c_str());
						bound[1] = atoi(upper_bound.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<uint32_t>(ctx, dim_name, bound, extent);

					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added uint32 dimension:" << dim_name << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT64)
				{
					int64_t extent = 10;
					std::array<int64_t, 2> bound;
					bound[0] = std::numeric_limits<int64_t>::min() / extent;
					bound[1] = (std::numeric_limits<int64_t>::max() / extent) - extent;
					if ((!lower_bound.empty()) && (!upper_bound.empty()))
					{
						bound[0] = atoll(lower_bound.c_str());
						bound[1] = atoll(upper_bound.c_str());
					}
					tiledb::Dimension dim = tiledb::Dimension::create<int64_t>(ctx, dim_name, bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added int64 dimension:" << dim_name << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT64)
				{
					uint64_t extent = 10;
					std::array<uint64_t, 2> bound;
					bound[0] = std::numeric_limits<uint64_t>::min() / extent;
					bound[1] = (std::numeric_limits<uint64_t>::max() / extent) - extent;
					if ((!lower_bound.empty()) && (!upper_bound.empty()))
					{
						bound[0] = atoll(lower_bound.c_str());
						bound[1] = atoll(upper_bound.c_str());
					}
					tiledb::Dimension dim = tiledb::Dimension::create<uint64_t>(ctx, dim_name, bound, extent);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added uint64 dimension:" << dim_name << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_FLOAT64)
				{
					double extent = 10;
					std::array<double, 2> bound;
					bound[0] = int64_t(std::numeric_limits<double>::min() / extent);
					bound[1] = int64_t((std::numeric_limits<double>::max() / extent) - extent);
					if ((!lower_bound.empty()) && (!upper_bound.empty()))
					{
						bound[0] = atof(lower_bound.c_str());
						bound[1] = atof(upper_bound.c_str());
					}

					tiledb::Dimension dim = tiledb::Dimension::create<double>(ctx, dim_name, bound, 10);
					dim.set_filter_list(filter_list);
					domain.add_dimension(dim);
					std::cout << "added float64 dimension:" << dim_name << std::endl;
				}
				else
				{
					std::cout << "not implemented type:" << tiledb_datatype << ", for field:" << dim_name << std::endl;
				}


			}//for (auto& dim_name : dim_names)

			 //set domain
			schema.set_domain(domain);
			schema.set_cell_order(TILEDB_ROW_MAJOR);
			schema.set_tile_order(TILEDB_ROW_MAJOR);


			std::vector<std::string> attr_names = datamap->attribute_names();
			for (auto& attr_name : attr_names)
			{
				if (!datamap->has_column(attr_name))
				{
					continue;
				}
				std::shared_ptr<tiledb::ColumnData> column = datamap->columns()[attr_name];
				tiledb_datatype_t tiledb_datatype = column->datatype();

				if (tiledb_datatype == tiledb_datatype_t::TILEDB_CHAR
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS2
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS4
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF16
					|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF32
					)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<std::string>(ctx, attr_name);//  //attr(ctx, field->name(), tiledb_datatype);
																									//				attr.set_cell_val_num(TILEDB_VAR_NUM);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added string attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT32)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<int>(ctx, attr_name);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added int attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT64)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<int64_t>(ctx, attr_name);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added int64 attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT32)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<uint32_t>(ctx, attr_name);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added uint32_t attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT64)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<uint64_t>(ctx, attr_name);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added uint64_t attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else if (tiledb_datatype == tiledb_datatype_t::TILEDB_FLOAT64)
				{
					tiledb::Attribute attr = tiledb::Attribute::create<double>(ctx, attr_name);
					attr.set_filter_list(filter_list);
					schema.add_attribute(attr);
					std::cout << "added double attribute:" << attr_name << ",datatype:" << tiledb_datatype << std::endl;
				}
				else
				{
					std::cout << "not implemented type:" << tiledb_datatype << ", for field:" << attr_name << std::endl;
				}



			}//for (auto& attr_name : attr_names)

			tiledb::Array::create(uri, schema); //create array

			tiledb::Array arr(ctx, uri, tiledb_query_type_t::TILEDB_WRITE);
			tiledb::Query query(ctx, arr, tiledb_query_type_t::TILEDB_WRITE);
			query.set_layout(tiledb_layout_t::TILEDB_UNORDERED);

			for (auto& column : datamap->columns())
			{
				column.second->set_buffer();
				if (column.second->is_var())
				{
					ctx.handle_error(tiledb_query_set_buffer_var(
						ctx.ptr().get(),
						query.ptr().get(),
						column.second->name().c_str(),
						column.second->offsets(),
						&(column.second->offset_bytes_size()),
						column.second->data(),
						&(column.second->data_bytes_size())
					));
				}
				else
				{
					ctx.handle_error(tiledb_query_set_buffer(
						ctx.ptr().get(),
						query.ptr().get(),
						column.second->name().c_str(),
						column.second->data(), //buff,
						&(column.second->data_bytes_size())));

				}
			}//for (auto& column : datamap->columns())

			 //submit
			ctx.handle_error(tiledb_query_submit(ctx.ptr().get(), query.ptr().get()));

			tiledb_query_status_t query_status;
			ctx.handle_error(
				tiledb_query_get_status(ctx.ptr().get(), query.ptr().get(), &query_status));

			if (query_status != tiledb_query_status_t::TILEDB_COMPLETED)
			{
				std::cout << "ArrayUtil::write_from_columndatamap, NOT completed query_status:" << query_status << ",uri:" << uri << ", with query_str:" << json_str << std::endl;
			}

			arr.close(); //close the array
		}
		catch (tiledb::TileDBError& tdberror)
		{
			std::cout << "ArrayUtil::write_from_columndatamap, got error:" << tdberror.what() << ",uri:" << uri << ", with query_str:" << json_str << std::endl;

		}
		catch (...)
		{
			std::cout << "ArrayUtil::write_from_columndatamap, got unknown error!" << ",uri:" << uri << ", with query_str:" << json_str << std::endl;
		}



		return;
	}//void ArrayUtil::write_from_columndatamap(const std::string& uri, const std::shared_ptr<tiledb::ColumnDataMap>& datamap, const std::string& json_str)

	void ArrayUtil::write_from_arrow_table(const std::string& uri, const std::shared_ptr<arrow::Table>& table, const std::string& json_str)
	{
		if (!table)
		{
			std::cout << "ArrayUtil::write_from_arrow_table, null table!" << std::endl;
			return;
		}
		std::shared_ptr<ColumnDataMap> datamap = get_columndatamap_from_arrow_table(table);
		write_from_columndatamap(uri,datamap, json_str);
	
	}//static void write_from_arrow_table

	void ArrayUtil::write_from_pyarrow(const std::string& uri, pybind11::object& pyobj, const std::string& json_str)
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

			write_from_arrow_table(uri, table, json_str);
		}

	}//static void write_from_pyarrow

	std::shared_ptr<tiledb::ColumnDataMap> ArrayUtil::get_columndatamap_from_arrow_table(const std::shared_ptr<arrow::Table>& table)
	{
		std::shared_ptr<tiledb::ColumnDataMap> datamap = std::shared_ptr<tiledb::ColumnDataMap>(new tiledb::ColumnDataMap());

		if (!table)
		{
			std::cout << "ArrayUtil::get_columndatamap_from_arrow_table, null table!" << std::endl;
			return datamap;
		}

		int nfields = (int)table->fields().size();
		int ncols = table->num_columns();
		int64_t nrows = table->num_rows();

		for (int i = 0; i < nfields; ++i) //(auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)
		{
			const std::shared_ptr<arrow::Field>& field = table->field(i);// (*itfield);
			std::shared_ptr<arrow::DataType> arrow_datatype = field->type();
			tiledb_datatype_t tiledb_datatype = arrow_datatype_to_tiledb(field->type());

			auto arrow_arr = table->GetColumnByName(field->name());

			if (arrow_datatype->id() == arrow::Type::STRING)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_STRING_ASCII);
				std::shared_ptr<StringColumnData> string_column = std::dynamic_pointer_cast<StringColumnData>(datamap->columns()[field->name()]);

				if (string_column)
				{
					string_column->data_vector().clear();
					string_column->offsets_vector().clear();
					string_column->bytes_vector().clear();

					string_column->data_vector().reserve(table->num_rows());
					string_column->offsets_vector().reserve(table->num_rows());
					string_column->bytes_vector().reserve(table->num_rows());

					uint64_t offset = 0;

					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::StringArray>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							std::string value_str = arrow_array->GetString(i);
							string_column->bytes_vector().insert(string_column->bytes_vector().end(), value_str.begin(), value_str.end());

							string_column->data_vector().emplace_back(value_str);
							string_column->offsets_vector().push_back(offset);
							
							offset += value_str.size();
						}
					}


				}

			}
			else if (arrow_datatype->id() == arrow::Type::INT32)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_INT32);
				std::shared_ptr<Int32ColumnData> int32_column = std::dynamic_pointer_cast<Int32ColumnData>(datamap->columns()[field->name()]);
				if (int32_column)
				{
					int32_column->data_vector().reserve(table->num_rows());
					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::Int32Array>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							int32_column->data_vector().push_back(arrow_array->Value(i));
						}
					}
				}
			}
			else if (arrow_datatype->id() == arrow::Type::UINT32)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_UINT32);
				std::shared_ptr<UInt32ColumnData> uint32_column = std::dynamic_pointer_cast<UInt32ColumnData>(datamap->columns()[field->name()]);
				if (uint32_column)
				{
					uint32_column->data_vector().reserve(table->num_rows());
					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::UInt32Array>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							uint32_column->data_vector().push_back(arrow_array->Value(i));
						}
					}
				}
			}
			else if (arrow_datatype->id() == arrow::Type::INT64)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_INT64);
				std::shared_ptr<Int64ColumnData> int64_column = std::dynamic_pointer_cast<Int64ColumnData>(datamap->columns()[field->name()]);
				if (int64_column)
				{
					int64_column->data_vector().reserve(table->num_rows());
					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::Int64Array>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							int64_column->data_vector().push_back(arrow_array->Value(i));
						}
					}
				}
			}
			else if (arrow_datatype->id() == arrow::Type::UINT64)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_UINT64);
				std::shared_ptr<UInt64ColumnData> uint64_column = std::dynamic_pointer_cast<UInt64ColumnData>(datamap->columns()[field->name()]);
				if (uint64_column)
				{
					uint64_column->data_vector().reserve(table->num_rows());
					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::UInt64Array>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							uint64_column->data_vector().push_back(arrow_array->Value(i));
						}
					}
				}
			}
			else if (arrow_datatype->id() == arrow::Type::DOUBLE)
			{
				datamap->add_data_column(field->name(), tiledb_datatype_t::TILEDB_FLOAT64);
				std::shared_ptr<DoubleColumnData> double_column = std::dynamic_pointer_cast<DoubleColumnData>(datamap->columns()[field->name()]);
				if (double_column)
				{
					double_column->data_vector().reserve(table->num_rows());
					for (auto itchunk = arrow_arr->chunks().begin(); itchunk != arrow_arr->chunks().end(); ++itchunk)
					{
						auto arrow_array = std::static_pointer_cast<arrow::DoubleArray>(*itchunk);
						for (int64_t i = 0; i < arrow_array->length(); ++i)
						{
							double_column->data_vector().push_back(arrow_array->Value(i));
						}
					}
				}
			}
			else
			{
				std::cout << "not implemented type:" << arrow_datatype->id() << std::endl;
			}

			if (field->HasMetadata() && datamap->has_column(field->name()))
			{
				auto& column = datamap->columns()[field->name()];
				if (field->metadata()->Get("is_dim").ok())
				{
					if (field->metadata()->Get("is_dim").ValueUnsafe() == "1")
					{
						column->set_is_dim(true);
					}
				}
				if (field->metadata()->Get("lower_bound").ok())
				{
					column->set_lower_bound(field->metadata()->Get("lower_bound").ValueUnsafe());
				}
				if (field->metadata()->Get("upper_bound").ok())
				{
					column->set_upper_bound(field->metadata()->Get("upper_bound").ValueUnsafe());
				}
			}//if (field->HasMetadata() && datamap->has_column(field->name()))

		}//for (auto itfield = table->fields().begin(); itfield != table->fields().end(); ++itfield)


		return datamap;
	}//std::shared_ptr<tiledb::ColumnDataMap> ArrayUtil::get_columndatamap_from_arrow_table

	std::shared_ptr<tiledb::ColumnDataMap> ArrayUtil::get_columndatamap_from_pyarrow(pybind11::object& pyobj)
	{
		std::shared_ptr<tiledb::ColumnDataMap> datamap = std::shared_ptr<tiledb::ColumnDataMap>(new tiledb::ColumnDataMap());

		arrow::py::import_pyarrow();
		if (pyobj.is_none())
		{
			std::cout << "ArrayUtil::get_columndatamap_from_pyarrow, pyobj is None" << std::endl;
			return datamap;
		}

		//	std::cout << "start to unwrap_table for pyobj..." << std::endl;
		auto result = arrow::py::unwrap_table(pyobj.ptr());

		if (!result.status().ok())
		{
			std::cout << "ArrayUtil::get_columndatamap_from_pyarrow,failed to unwrap_table,status:" << result.status() << std::endl;
		}
		else
		{
			std::cout << "ArrayUtil::get_columndatamap_from_pyarrow, finished unwrap_table, status:" << result.status() << std::endl;
		}

		{
			pybind11::gil_scoped_release scoped_release;

			std::shared_ptr<arrow::Table> table = result.ValueOrDie();

			datamap = get_columndatamap_from_arrow_table(table);
		}
		return datamap;
	}

	std::shared_ptr<arrow::Table> ArrayUtil::get_arrow_table_from_columndatamap(const std::shared_ptr<tiledb::ColumnDataMap>& datamap)
	{
		if (!datamap)
		{
			return std::shared_ptr<arrow::Table>(nullptr);
		}

		std::vector<std::shared_ptr<arrow::Field>> fields;
		std::vector<std::shared_ptr<arrow::Array>> arrow_arrays;

		for (auto& column : datamap->columns())
		{
			std::shared_ptr<arrow::KeyValueMetadata> kvmeta = std::shared_ptr<arrow::KeyValueMetadata>(new arrow::KeyValueMetadata());
			if (column.second->is_dim())
			{
				kvmeta->Append("is_dim", "1");
				kvmeta->Append("lower_bound", column.second->lower_bound());
				kvmeta->Append("upper_bound", column.second->upper_bound());
			}
			std::shared_ptr<arrow::DataType> arrow_data_type = tiledb_datatype_to_arrow(column.second->datatype());
			std::shared_ptr<arrow::Field> field = std::shared_ptr<arrow::Field>(new arrow::Field(column.second->name(), arrow_data_type, true, kvmeta));
			fields.emplace_back(field);
			
			tiledb_datatype_t tiledb_datatype = column.second->datatype();
			if (tiledb_datatype == tiledb_datatype_t::TILEDB_CHAR
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_ASCII
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF8
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS2
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UCS4
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF16
				|| tiledb_datatype == tiledb_datatype_t::TILEDB_STRING_UTF32
				)
			{
				std::shared_ptr<tiledb::StringColumnData> string_column = std::dynamic_pointer_cast<tiledb::StringColumnData>(column.second);
				if (string_column)
				{
					arrow::StringBuilder builder;
					builder.Resize(string_column->offsets_vector().size());
					builder.AppendValues(string_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT32)
			{
				std::shared_ptr<tiledb::Int32ColumnData> int32_column = std::dynamic_pointer_cast<tiledb::Int32ColumnData>(column.second);
				if (int32_column)
				{
					arrow::Int32Builder builder;
					builder.Resize(int32_column->data_vector().size());
					builder.AppendValues(int32_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT32)
			{
				std::shared_ptr<tiledb::UInt32ColumnData> uint32_column = std::dynamic_pointer_cast<tiledb::UInt32ColumnData>(column.second);
				if (uint32_column)
				{
					arrow::UInt32Builder builder;
					builder.Resize(uint32_column->data_vector().size());
					builder.AppendValues(uint32_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_INT64)
			{
				std::shared_ptr<tiledb::Int64ColumnData> int64_column = std::dynamic_pointer_cast<tiledb::Int64ColumnData>(column.second);
				if (int64_column)
				{
					arrow::Int64Builder builder;
					builder.Resize(int64_column->data_vector().size());
					builder.AppendValues(int64_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_UINT64)
			{
				std::shared_ptr<tiledb::UInt64ColumnData> uint64_column = std::dynamic_pointer_cast<tiledb::UInt64ColumnData>(column.second);
				if (uint64_column)
				{
					arrow::UInt64Builder builder;
					builder.Resize(uint64_column->data_vector().size());
					builder.AppendValues(uint64_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else if (tiledb_datatype == tiledb_datatype_t::TILEDB_FLOAT64)
			{
				std::shared_ptr<tiledb::DoubleColumnData> double_column = std::dynamic_pointer_cast<tiledb::DoubleColumnData>(column.second);
				if (double_column)
				{
					arrow::DoubleBuilder builder;
					builder.Resize(double_column->data_vector().size());
					builder.AppendValues(double_column->data_vector());

					std::shared_ptr<arrow::Array> array;
					arrow::Status status = builder.Finish(&array);
					if (array)
					{
						arrow_arrays.emplace_back(array);
					}
				}
			}
			else
			{
				std::cout << "ArrayUtil::get_arrow_table_from_columndatamap, not implemented datatype:" << tiledb_datatype << std::endl;
			}



		}//for (auto& column : datamap->columns())

		//////
		std::shared_ptr<arrow::Schema> arrowschema = std::make_shared<arrow::Schema>(fields);
//		std::cout << "got arrow_schema:" << arrowschema->ToString() << std::endl;

		std::shared_ptr<arrow::Table> result = arrow::Table::Make(arrowschema, arrow_arrays);
		return result;
	}//std::shared_ptr<arrow::Table> ArrayUtil::get_arrow_table_from_columndatamap
 
	pybind11::object ArrayUtil::get_pyarrow_from_columndatamap(const std::shared_ptr<tiledb::ColumnDataMap>& datamap)
	{
		std::shared_ptr<arrow::Table> table = get_arrow_table_from_columndatamap(datamap);
		if (!table)
		{
		//	throw pybind11::buffer_error("error in read_to_pyarrow!");
			return pybind11::object();
		}
 
		arrow::py::import_pyarrow();
		return pybind11::reinterpret_steal<pybind11::object>(pybind11::handle(arrow::py::wrap_table(table)));
	}

	int ArrayUtil::get_data_offsets_for_arrow_table_string_field(const std::shared_ptr<arrow::Table> & table, int i, std::string& data, std::vector<uint64_t>& offsets)
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
	int ArrayUtil::get_data_offsets_for_string_vector(const std::vector<std::string>& buffer, std::string& data, std::vector<uint64_t>& offsets)
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

	tiledb_datatype_t ArrayUtil::arrow_datatype_to_tiledb(const std::shared_ptr<arrow::DataType> & data_type)
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

	std::shared_ptr<arrow::DataType> ArrayUtil::tiledb_datatype_to_arrow(tiledb_datatype_t data_type) {
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
		case tiledb_datatype_t::TILEDB_CHAR:
			return std::make_shared<arrow::StringType>();
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_int32_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_int64_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_uint32_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_uint64_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_double_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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
	std::shared_ptr<arrow::Array> ArrayUtil::read_var_size_buffer_to_arrow_array(const std::string& uri, const std::string& name)
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



}//namespace
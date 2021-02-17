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
//#include <codecvt>

#include "tiledb_cxx_array.h"
#include "tiledb_cxx_array_schema.h"
#include "tiledb_cxx_attribute.h"
#include "tiledb_cxx_config.h"
#include "tiledb_cxx_context.h"
#include "tiledb_cxx_deleter.h"
#include "tiledb_cxx_dimension.h"
#include "tiledb_cxx_domain.h"
#include "tiledb_cxx_exception.h"
#include "tiledb_cxx_filter.h"
#include "tiledb_cxx_filter_list.h"
#include "tiledb_cxx_group.h"
#include "tiledb_cxx_object.h"
#include "tiledb_cxx_object_iter.h"
#include "tiledb_cxx_query.h"
#include "tiledb_cxx_schema_base.h"
#include "tiledb_cxx_stats.h"
#include "tiledb.h"
#include "tiledb_cxx_utils.h"
#include "tiledb_cxx_version.h"
#include "tiledb_cxx_vfs.h"

#include "tiledb_cxx_column.h"

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

public:
	/**
	* @brief get version
	*
	* @return version string
	*/
	static std::string get_version();
 
	/**
	* @name accessor helper functions
	*/
	///@{

	/**
	* @brief get dimension names of schema
	*
	* @param schema
	*
	* @return names
	*/
	static std::vector<std::string> dimension_names_of_array_schema(const tiledb::ArraySchema& schema);

	/**
	* @brief get attribute names of schema
	*
	* @param schema
	*
	* @return names
	*/
	static std::vector<std::string> attribute_names_of_array_schema(const tiledb::ArraySchema& schema);

	/**
	* @brief get coordinate filter names of schema
	*
	* @param schema
	*
	* @return names
	*/
	static std::vector<std::string> coords_filter_names_of_array_schema(tiledb::ArraySchema& schema);

	/**
	* @brief get offset filter names of schema
	*
	* @param schema
	*
	* @return names
	*/
	static std::vector<std::string> offsets_filter_names_of_array_schema(tiledb::ArraySchema& schema);

	/**
	* @brief get dimension filter names of schema
	*
	* @param schema
	* @param name
	*
	* @return filter names
	*/
	static std::vector<std::string> dimension_filter_names_of_array_schema(const tiledb::ArraySchema& schema, const std::string& name);

	/**
	* @brief get attribute filter names of schema
	*
	* @param schema
	* @param name
	*
	* @return filter names
	*/
	static std::vector<std::string> attribute_filter_names_of_array_schema(const tiledb::ArraySchema& schema, const std::string& name);

	/**
	* @brief get datatype of dimension or attribute 
	*
	* @param schema
	* @param name
	*
	* @return datatype
	*/
	static tiledb_datatype_t datatype_of_dimension_or_attribute(tiledb::ArraySchema& schema, const std::string& name);
 
	/**
	* @brief get json string of schema
	*
	* @param schema
	*
	* @return json string
	*/
	static std::string json_str_of_array_schema(const tiledb::ArraySchema& schema);


	/**
	* @brief create ArraySchema from json string
	*
	* @param json_str
	*
	* @return array schema
	*/
	static tiledb::ArraySchema json_str_to_array_schema(const std::string& json_str);

	///@}
    
	/**
	* @name reader functions
	*/
	///@{
	/**
	* @brief get int vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<int> get_int32_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief get uint32 vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<uint32_t> get_uint32_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief get int64 vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<int64_t> get_int64_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief get uint64 vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<uint64_t> get_uint64_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief get double vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<double> get_double_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief get string vector from uri
	*
	* @param uri
	* @param name
	*
	* @return data vector
	*/
	static std::vector<std::string> get_string_vector_from_uri(const std::string& uri, const std::string& name);

	/**
	* @brief read from uri to arrow table
	*
	* @param uri
	* @param json_str for query information
	*
	* @return arrow table
	*/
	static std::shared_ptr<arrow::Table>  read_to_arrow_talbe(const std::string& uri, const std::string& json_str);

	/**
	* @brief read from uri to pyobject of arrow table
	*
	* @param uri
	* @param selected columns to read
	*
	* @return pyobject of arrow table
	*/
	static pybind11::object read_to_pyarrow(const std::string& uri, const std::string& json_str);

	
	/**
	* @brief read to ColumnDataMap 
	*
	* @param uri
	* @param query json string
	*
	* @return ColumnDataMap
	*/
	static std::shared_ptr<tiledb::ColumnDataMap> read_to_columndatamap(const std::string& uri, const std::string& query_str);
	
	///@}

	/**
	* @name write functions
	*/
	///@{
	/**
	* @brief write ColumnDataMap data to uri
	*
	* @param uri
	* @param datamap
	* @param json_str for query information
	*/
	static void write_from_columndatamap(const std::string& uri, const std::shared_ptr<tiledb::ColumnDataMap>& datamap, const std::string& json_str);

	/**
	* @brief write arrow table to uri
	*
	* @param uri
	* @param arrow table
	* @param dimension columns
	*/
	static void write_from_arrow_table(const std::string& uri, const std::shared_ptr<arrow::Table>& table, const std::string& json_str);

	/**
	* @brief write arrow table to uri
	*
	* @param uri
	* @param pyobject arrow table
	* @param dimension columns
	*/
	static void write_from_pyarrow(const std::string& uri, pybind11::object& pyobj, const std::string& json_str);

	///@}



	/**
	* @brief get ColumnDataMap data buffer from arrow table
	*/
	static std::shared_ptr<tiledb::ColumnDataMap> get_columndatamap_from_arrow_table(const std::shared_ptr<arrow::Table>& table);

	/**
	* @brief get ColumnDataMap from pyarrow table
	*/
	static std::shared_ptr<tiledb::ColumnDataMap> get_columndatamap_from_pyarrow(pybind11::object& pyobj);

	/**
	* @brief get arrow table from ColumnDataMap data buffer
	*
	* @param column datamap
	*
	* @return arrow table
	*/
	static std::shared_ptr<arrow::Table> get_arrow_table_from_columndatamap(const std::shared_ptr<tiledb::ColumnDataMap>& datamap);

	/**
	* @brief get pyarrow from ColumnDataMap
	*
	* @param column datamap
	*
	* @return pyarrow table
	*/
	static pybind11::object get_pyarrow_from_columndatamap(const std::shared_ptr<tiledb::ColumnDataMap>& datamap);
protected:
	static int get_data_offsets_for_arrow_table_string_field(const std::shared_ptr<arrow::Table> & table, int i, std::string& data, std::vector<uint64_t>& offsets);
	static int get_data_offsets_for_string_vector(const std::vector<std::string>& buffer, std::string& data, std::vector<uint64_t>& offsets);

	static tiledb_datatype_t arrow_datatype_to_tiledb(const std::shared_ptr<arrow::DataType> & data_type);

	static std::shared_ptr<arrow::DataType> tiledb_datatype_to_arrow(tiledb_datatype_t data_type);

 
	static std::shared_ptr<arrow::Array> read_int32_buffer_to_arrow_array(const std::string& uri, const std::string& name);

 
	static std::shared_ptr<arrow::Array> read_int64_buffer_to_arrow_array(const std::string& uri, const std::string& name);

 
	static std::shared_ptr<arrow::Array> read_uint32_buffer_to_arrow_array(const std::string& uri, const std::string& name);

 
	static std::shared_ptr<arrow::Array> read_uint64_buffer_to_arrow_array(const std::string& uri, const std::string& name);

 
	static std::shared_ptr<arrow::Array> read_double_buffer_to_arrow_array(const std::string& uri, const std::string& name);

 
	static std::shared_ptr<arrow::Array> read_var_size_buffer_to_arrow_array(const std::string& uri, const std::string& name);


};//class ArrayUtil


 

 


}//namespace 

#endif

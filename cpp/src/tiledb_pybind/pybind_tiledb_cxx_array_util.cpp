#include "pybind_tiledb_cxx_array_util.h" 

void init_tiledb_ArrayUtil(pybind11::module& m) {
	pybind11::class_<tiledb::ArrayUtil>(m,"ArrayUtil")
//ignore_constructor_staticclass 	 ArrayUtil()
//ignore_constructor_staticclass 	 ArrayUtil( const tiledb::ArrayUtil & from)
//ignore_keywords 	ArrayUtil & operator=( const tiledb::ArrayUtil & from)
//ignore_destructor 	virtual  ~ArrayUtil()
		.def_static("get_version", &tiledb::ArrayUtil::get_version)
		.def_static("dimension_names_of_array_schema", &tiledb::ArrayUtil::dimension_names_of_array_schema, py::arg("schema"))
		.def_static("attribute_names_of_array_schema", &tiledb::ArrayUtil::attribute_names_of_array_schema, py::arg("schema"))
		.def_static("coords_filter_names_of_array_schema", &tiledb::ArrayUtil::coords_filter_names_of_array_schema, py::arg("schema"))
		.def_static("offsets_filter_names_of_array_schema", &tiledb::ArrayUtil::offsets_filter_names_of_array_schema, py::arg("schema"))
		.def_static("dimension_filter_names_of_array_schema", &tiledb::ArrayUtil::dimension_filter_names_of_array_schema, py::arg("schema"), py::arg("name"))
		.def_static("attribute_filter_names_of_array_schema", &tiledb::ArrayUtil::attribute_filter_names_of_array_schema, py::arg("schema"), py::arg("name"))
		.def_static("datatype_of_dimension_or_attribute", &tiledb::ArrayUtil::datatype_of_dimension_or_attribute, py::arg("schema"), py::arg("name"))
		.def_static("json_str_of_array_schema", &tiledb::ArrayUtil::json_str_of_array_schema, py::arg("schema"))
		.def_static("json_str_to_array_schema", &tiledb::ArrayUtil::json_str_to_array_schema, py::arg("json_str"))
		.def_static("get_int32_vector_from_uri", &tiledb::ArrayUtil::get_int32_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_uint32_vector_from_uri", &tiledb::ArrayUtil::get_uint32_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_int64_vector_from_uri", &tiledb::ArrayUtil::get_int64_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_uint64_vector_from_uri", &tiledb::ArrayUtil::get_uint64_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_double_vector_from_uri", &tiledb::ArrayUtil::get_double_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_string_vector_from_uri", &tiledb::ArrayUtil::get_string_vector_from_uri, py::arg("uri"), py::arg("name"))
//ignore_keywords 	std::shared_ptr<arrow::Table > read_to_arrow_talbe( const std::string & uri, const std::string & json_str)
		.def_static("read_to_pyarrow", &tiledb::ArrayUtil::read_to_pyarrow, py::arg("uri"), py::arg("json_str"))
		.def_static("read_to_columndatamap", &tiledb::ArrayUtil::read_to_columndatamap, py::arg("uri"), py::arg("query_str"))
		.def_static("write_from_columndatamap", &tiledb::ArrayUtil::write_from_columndatamap, py::arg("uri"), py::arg("datamap"), py::arg("json_str"))
//ignore_keywords 	void write_from_arrow_table( const std::string & uri, const std::shared_ptr<arrow::Table> & table, const std::string & json_str)
		.def_static("write_from_pyarrow", &tiledb::ArrayUtil::write_from_pyarrow, py::arg("uri"), py::arg("pyobj"), py::arg("json_str"))
//ignore_keywords 	std::shared_ptr<tiledb::ColumnDataMap > get_columndatamap_from_arrow_table( const std::shared_ptr<arrow::Table> & table)
		.def_static("get_columndatamap_from_pyarrow", &tiledb::ArrayUtil::get_columndatamap_from_pyarrow, py::arg("pyobj"))
//ignore_keywords 	std::shared_ptr<arrow::Table > get_arrow_table_from_columndatamap( const std::shared_ptr<tiledb::ColumnDataMap> & datamap)
		.def_static("get_pyarrow_from_columndatamap", &tiledb::ArrayUtil::get_pyarrow_from_columndatamap, py::arg("datamap"))
		;

}


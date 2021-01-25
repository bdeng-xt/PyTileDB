#include "pybind_array_util.h" 

void init_tiledb_ArrayUtil(pybind11::module& m) {
	pybind11::class_<tiledb::ArrayUtil>(m,"ArrayUtil")
		.def(py::init<>())
		.def(py::init<const tiledb::ArrayUtil &>())
//ignore_keywords 	ArrayUtil & operator=( const tiledb::ArrayUtil & from)
//ignore_destructor 	virtual  ~ArrayUtil()
		.def_static("get_version", &tiledb::ArrayUtil::get_version)
		.def_static("open_array", &tiledb::ArrayUtil::open_array, py::arg("ctx"), py::arg("uri"), py::arg("rw"))
		.def_static("dimension_names_of_array_schema", &tiledb::ArrayUtil::dimension_names_of_array_schema, py::arg("schema"))
		.def_static("attribute_names_of_array_schema", &tiledb::ArrayUtil::attribute_names_of_array_schema, py::arg("schema"))
		.def_static("coords_filter_names_of_array_schema", &tiledb::ArrayUtil::coords_filter_names_of_array_schema, py::arg("schema"))
		.def_static("offsets_filter_names_of_array_schema", &tiledb::ArrayUtil::offsets_filter_names_of_array_schema, py::arg("schema"))
		.def_static("dimension_filter_names_of_array_schema", &tiledb::ArrayUtil::dimension_filter_names_of_array_schema, py::arg("schema"), py::arg("name"))
		.def_static("attribute_filter_names_of_array_schema", &tiledb::ArrayUtil::attribute_filter_names_of_array_schema, py::arg("schema"), py::arg("name"))
		.def_static("datatype_of_dimension_or_attribute", &tiledb::ArrayUtil::datatype_of_dimension_or_attribute, py::arg("schema"), py::arg("name"))
		.def_static("add_coords_filter_to_array_schema", &tiledb::ArrayUtil::add_coords_filter_to_array_schema, py::arg("ctx"), py::arg("schema"), py::arg("filter_type"))
		.def_static("add_offsets_filter_to_array_schema", &tiledb::ArrayUtil::add_offsets_filter_to_array_schema, py::arg("ctx"), py::arg("schema"), py::arg("filter_type"))
		.def_static("add_dimension_filter_to_array_schema", &tiledb::ArrayUtil::add_dimension_filter_to_array_schema, py::arg("ctx"), py::arg("schema"), py::arg("dim_name"), py::arg("filter_type"))
		.def_static("add_attribute_filter_to_array_schema", &tiledb::ArrayUtil::add_attribute_filter_to_array_schema, py::arg("ctx"), py::arg("schema"), py::arg("attr_name"), py::arg("filter_type"))
		.def_static("json_str_of_array_schema", &tiledb::ArrayUtil::json_str_of_array_schema, py::arg("schema"))
		.def_static("make_query", &tiledb::ArrayUtil::make_query, py::arg("ctx"), py::arg("arr"), py::arg("query_type"))
		.def_static("set_int32_buffer_for_query", &tiledb::ArrayUtil::set_int32_buffer_for_query, py::arg("query"), py::arg("name"), py::arg("buffer"))
		.def_static("set_int64_buffer_for_query", &tiledb::ArrayUtil::set_int64_buffer_for_query, py::arg("query"), py::arg("name"), py::arg("buffer"))
		.def_static("set_double_buffer_for_query", &tiledb::ArrayUtil::set_double_buffer_for_query, py::arg("query"), py::arg("name"), py::arg("buffer"))
		.def_static("set_string_buffer_for_query", &tiledb::ArrayUtil::set_string_buffer_for_query, py::arg("query"), py::arg("name"), py::arg("buffer"))
		.def_static("get_int32_vector_from_uri", &tiledb::ArrayUtil::get_int32_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_uint32_vector_from_uri", &tiledb::ArrayUtil::get_uint32_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_int64_vector_from_uri", &tiledb::ArrayUtil::get_int64_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_uint64_vector_from_uri", &tiledb::ArrayUtil::get_uint64_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_double_vector_from_uri", &tiledb::ArrayUtil::get_double_vector_from_uri, py::arg("uri"), py::arg("name"))
		.def_static("get_string_vector_from_uri", &tiledb::ArrayUtil::get_string_vector_from_uri, py::arg("uri"), py::arg("name"))
//ignore_keywords 	std::shared_ptr<arrow::Table > read_to_arrow_talbe( const std::string & uri, const std::vector<std::string> & columns)
		.def_static("read_to_pyarrow", &tiledb::ArrayUtil::read_to_pyarrow, py::arg("uri"), py::arg("columns"))
//ignore_keywords 	void write_from_arrow_table( const std::string & uri, const std::shared_ptr<arrow::Table> & table, std::vector<std::string> & dim_columns)
		.def_static("write_from_pyarrow", &tiledb::ArrayUtil::write_from_pyarrow, py::arg("uri"), py::arg("pyobj"), py::arg("dim_columns"))
		;

}

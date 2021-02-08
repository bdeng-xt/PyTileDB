#include "pybind_column.h" 

void init_tiledb_ColumnData(pybind11::module& m) {
	pybind11::class_<tiledb::ColumnData, std::shared_ptr<tiledb::ColumnData> >(m,"ColumnData")
		.def(py::init<>())
		.def(py::init<const tiledb::ColumnData &>())
//ignore_keywords 	ColumnData & operator=( const tiledb::ColumnData & from)
		.def(py::init<tiledb::ColumnData &>())
//ignore_keywords 	tiledb::ColumnData & operator=( tiledb::ColumnData & &)
//ignore_destructor 	virtual  ~ColumnData()
		.def("name", &tiledb::ColumnData::name)
		.def("set_name", &tiledb::ColumnData::set_name, py::arg("s"))
		.def("datatype", &tiledb::ColumnData::datatype)
		.def("set_datatype", &tiledb::ColumnData::set_datatype, py::arg("t"))
		.def("offsets", &tiledb::ColumnData::offsets)
		.def("offset_nelements", &tiledb::ColumnData::offset_nelements)
		.def("offset_bytes_size", &tiledb::ColumnData::offset_bytes_size)
//ignore_keywords 	void * data()
		.def("data_nelements", &tiledb::ColumnData::data_nelements)
		.def("data_bytes_size", &tiledb::ColumnData::data_bytes_size)
		.def("data_element_size", &tiledb::ColumnData::data_element_size)
		.def("is_dim", &tiledb::ColumnData::is_dim)
		.def("set_is_dim", &tiledb::ColumnData::set_is_dim, py::arg("b"))
		.def("is_var", &tiledb::ColumnData::is_var)
		.def("set_is_var", &tiledb::ColumnData::set_is_var, py::arg("b"))
		.def("lower_bound", &tiledb::ColumnData::lower_bound)
		.def("set_lower_bound", &tiledb::ColumnData::set_lower_bound, py::arg("s"))
		.def("upper_bound", &tiledb::ColumnData::upper_bound)
		.def("set_upper_bound", &tiledb::ColumnData::set_upper_bound, py::arg("s"))
		.def("is_buffer_empty", &tiledb::ColumnData::is_buffer_empty)
		.def("reset_buffer", &tiledb::ColumnData::reset_buffer)
		.def("resize_vector", &tiledb::ColumnData::resize_vector, py::arg("sz"))
		.def("resize_bytes_vector", &tiledb::ColumnData::resize_bytes_vector, py::arg("sz"))
		.def("set_buffer", &tiledb::ColumnData::set_buffer)
		.def("read_buffer", &tiledb::ColumnData::read_buffer)
		.def("clear", &tiledb::ColumnData::clear)
		;

}


void init_tiledb_StringColumnData(pybind11::module& m) {
	pybind11::class_<tiledb::StringColumnData, std::shared_ptr<tiledb::StringColumnData> >(m,"StringColumnData")
		.def(py::init<>())
		.def(py::init<const tiledb::StringColumnData &>())
//ignore_keywords 	StringColumnData & operator=( const tiledb::StringColumnData & from)
		.def(py::init<tiledb::StringColumnData &>())
//ignore_keywords 	tiledb::StringColumnData & operator=( tiledb::StringColumnData & &)
//ignore_destructor 	virtual  ~StringColumnData()
		.def("data_vector", &tiledb::StringColumnData::data_vector)
		.def("bytes_vector", &tiledb::StringColumnData::bytes_vector)
		.def("offsets_vector", &tiledb::StringColumnData::offsets_vector)
		.def("resize_vector", &tiledb::StringColumnData::resize_vector, py::arg("sz"))
		.def("resize_bytes_vector", &tiledb::StringColumnData::resize_bytes_vector, py::arg("sz"))
		.def("set_buffer", &tiledb::StringColumnData::set_buffer)
		.def("read_buffer", &tiledb::StringColumnData::read_buffer)
		;

}


void init_tiledb_ColumnDataMap(pybind11::module& m) {
	pybind11::class_<tiledb::ColumnDataMap, std::shared_ptr<tiledb::ColumnDataMap> >(m,"ColumnDataMap")
		.def(py::init<>())
		.def(py::init<const tiledb::ColumnDataMap &>())
//ignore_keywords 	ColumnDataMap & operator=( const tiledb::ColumnDataMap & from)
		.def(py::init<tiledb::ColumnDataMap &>())
//ignore_keywords 	tiledb::ColumnDataMap & operator=( tiledb::ColumnDataMap & &)
//ignore_destructor 	virtual  ~ColumnDataMap()
//ignore_keywords 	std::unordered_map<std::string, std::shared_ptr<tiledb::ColumnData> > & columns()
		.def("has_column", &tiledb::ColumnDataMap::has_column, py::arg("column_name"))
		.def("offsets", &tiledb::ColumnDataMap::offsets, py::arg("column_name"))
		.def("offset_nelements", &tiledb::ColumnDataMap::offset_nelements, py::arg("column_name"))
		.def("offset_bytes_size", &tiledb::ColumnDataMap::offset_bytes_size, py::arg("column_name"))
//ignore_keywords 	void * data( const std::string & column_name)
		.def("data_nelements", &tiledb::ColumnDataMap::data_nelements, py::arg("column_name"))
		.def("data_bytes_size", &tiledb::ColumnDataMap::data_bytes_size, py::arg("column_name"))
		.def("data_element_size", &tiledb::ColumnDataMap::data_element_size, py::arg("column_name"))
		.def("is_dim", &tiledb::ColumnDataMap::is_dim, py::arg("column_name"))
		.def("set_is_dim", &tiledb::ColumnDataMap::set_is_dim, py::arg("column_name"), py::arg("b"))
		.def("is_var", &tiledb::ColumnDataMap::is_var, py::arg("column_name"))
		.def("set_is_var", &tiledb::ColumnDataMap::set_is_var, py::arg("column_name"), py::arg("b"))
		.def("lower_bound", &tiledb::ColumnDataMap::lower_bound, py::arg("column_name"))
		.def("set_lower_bound", &tiledb::ColumnDataMap::set_lower_bound, py::arg("column_name"), py::arg("s"))
		.def("upper_bound", &tiledb::ColumnDataMap::upper_bound, py::arg("column_name"))
		.def("set_upper_bound", &tiledb::ColumnDataMap::set_upper_bound, py::arg("column_name"), py::arg("s"))
		.def("is_buffer_empty", &tiledb::ColumnDataMap::is_buffer_empty, py::arg("column_name"))
		.def("is_empty", &tiledb::ColumnDataMap::is_empty)
		.def("column_by_name", &tiledb::ColumnDataMap::column_by_name, py::arg("column_name"))
		.def("ncol", &tiledb::ColumnDataMap::ncol)
		.def("nrows", &tiledb::ColumnDataMap::nrows, py::arg("column_name"))
		.def("dimension_names", &tiledb::ColumnDataMap::dimension_names)
		.def("dimension_datatypes", &tiledb::ColumnDataMap::dimension_datatypes)
		.def("attribute_names", &tiledb::ColumnDataMap::attribute_names)
		.def("attribute_datatypes", &tiledb::ColumnDataMap::attribute_datatypes)
		.def("add_column", &tiledb::ColumnDataMap::add_column, py::arg("column"))
		.def("add_data_column", &tiledb::ColumnDataMap::add_data_column, py::arg("column_name"), py::arg("datatype"))
		.def("add_vector_column", &tiledb::ColumnDataMap::add_vector_column, py::arg("column_name"), py::arg("datatype"))
		.def("get_int32_vector", &tiledb::ColumnDataMap::get_int32_vector, py::arg("column_name"))
		.def("get_uint32_vector", &tiledb::ColumnDataMap::get_uint32_vector, py::arg("column_name"))
		.def("get_int64_vector", &tiledb::ColumnDataMap::get_int64_vector, py::arg("column_name"))
		.def("get_uint64_vector", &tiledb::ColumnDataMap::get_uint64_vector, py::arg("column_name"))
		.def("get_double_vector", &tiledb::ColumnDataMap::get_double_vector, py::arg("column_name"))
		.def("get_string_vector", &tiledb::ColumnDataMap::get_string_vector, py::arg("column_name"))
		;

}

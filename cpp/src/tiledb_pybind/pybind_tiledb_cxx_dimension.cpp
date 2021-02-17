#include "pybind_tiledb_cxx_dimension.h" 

void init_tiledb_Dimension(pybind11::module& m) {
	pybind11::class_<tiledb::Dimension, std::shared_ptr<tiledb::Dimension> >(m,"Dimension")
//ignore_keywords 	 Dimension( const tiledb::Context & ctx, tiledb_dimension_t * dim)
		.def(py::init<const tiledb::Dimension>())
		.def(py::init<tiledb::Dimension &>())
//ignore_keywords 	tiledb::Dimension & operator=( const tiledb::Dimension &)
//ignore_keywords 	tiledb::Dimension & operator=( tiledb::Dimension & &)
		.def("cell_val_num", &tiledb::Dimension::cell_val_num)
		.def("set_cell_val_num", &tiledb::Dimension::set_cell_val_num, py::arg("num"))
		.def("filter_list", &tiledb::Dimension::filter_list)
		.def("set_filter_list", &tiledb::Dimension::set_filter_list, py::arg("filter_list"))
		.def("name", &tiledb::Dimension::name)
		.def("type", &tiledb::Dimension::type)
//ignore_keywords 	std::pair<T, T > domain()
		.def("domain_to_str", &tiledb::Dimension::domain_to_str)
//ignore_templatefunction 	T tile_extent()
		.def("tile_extent_to_str", &tiledb::Dimension::tile_extent_to_str)
//ignore_keywords 	std::shared_ptr<tiledb_dimension_t > ptr()
//ignore_templatefunction 	tiledb::Dimension create( const tiledb::Context & ctx, const std::string & name, const std::array<T, 2> & domain, T extent)
//ignore_keywords 	tiledb::Dimension create( const tiledb::Context & ctx, const std::string & name, tiledb_datatype_t datatype, const void * domain, const void * extent)
		.def_static("is_valid_intdatatype", &tiledb::Dimension::is_valid_intdatatype, py::arg("intdatatype"))
		.def_static("create_dimension", &tiledb::Dimension::create_dimension, py::arg("ctx"), py::arg("name"), py::arg("intdatatype"), py::arg("lower_bound_str"), py::arg("upper_bound_str"), py::arg("extent_str"))
		.def_static("create_int32_dimension", &tiledb::Dimension::create_int32_dimension, py::arg("ctx"), py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def_static("create_int64_dimension", &tiledb::Dimension::create_int64_dimension, py::arg("ctx"), py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def_static("create_uint64_dimension", &tiledb::Dimension::create_uint64_dimension, py::arg("ctx"), py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def_static("create_double_dimension", &tiledb::Dimension::create_double_dimension, py::arg("ctx"), py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def_static("create_string_dimension", &tiledb::Dimension::create_string_dimension, py::arg("ctx"), py::arg("name"))
		;

}


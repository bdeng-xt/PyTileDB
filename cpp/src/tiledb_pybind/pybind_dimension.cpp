#include "pybind_dimension.h" 

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
		;

}


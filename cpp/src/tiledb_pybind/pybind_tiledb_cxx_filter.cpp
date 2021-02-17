#include "pybind_tiledb_cxx_filter.h" 

void init_tiledb_Filter(pybind11::module& m) {
	pybind11::class_<tiledb::Filter, std::shared_ptr<tiledb::Filter> >(m,"Filter")
		.def(py::init<const tiledb::Context &,tiledb_filter_type_t>())
//ignore_keywords 	 Filter( const tiledb::Context & ctx, tiledb_filter_t * filter)
//ignore_constructor_deleted 	 Filter()
		.def(py::init<const tiledb::Filter>())
		.def(py::init<tiledb::Filter &>())
//ignore_keywords 	Filter & operator=( const tiledb::Filter &)
//ignore_keywords 	Filter & operator=( tiledb::Filter & &)
//ignore_keywords 	std::shared_ptr<tiledb_filter_t > ptr()
//ignore_templatefunction 	tiledb::Filter & set_option( tiledb_filter_option_t option, T value)
//ignore_keywords 	tiledb::Filter & set_option( tiledb_filter_option_t option, const void * value)
//ignore_templatefunction 	void get_option( tiledb_filter_option_t option, T * value)
//ignore_keywords 	void get_option( tiledb_filter_option_t option, void * value)
		.def("filter_type", &tiledb::Filter::filter_type)
		.def_static("to_str", &tiledb::Filter::to_str, py::arg("type"))
		;

}


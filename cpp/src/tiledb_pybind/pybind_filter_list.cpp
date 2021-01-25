#include "pybind_filter_list.h" 

void init_tiledb_FilterList(pybind11::module& m) {
	pybind11::class_<tiledb::FilterList, std::shared_ptr<tiledb::FilterList> >(m,"FilterList")
		.def(py::init<const tiledb::Context &>())
//ignore_keywords 	 FilterList( const tiledb::Context & ctx, tiledb_filter_list_t * filter_list)
//ignore_constructor_deleted 	 FilterList()
		.def(py::init<const tiledb::FilterList>())
		.def(py::init<tiledb::FilterList &>())
//ignore_keywords 	FilterList & operator=( const tiledb::FilterList &)
//ignore_keywords 	FilterList & operator=( tiledb::FilterList & &)
//ignore_keywords 	std::shared_ptr<tiledb_filter_list_t > ptr()
		.def("add_filter", &tiledb::FilterList::add_filter, py::arg("filter"))
		.def("filter", &tiledb::FilterList::filter, py::arg("filter_index"))
		.def("max_chunk_size", &tiledb::FilterList::max_chunk_size)
		.def("nfilters", &tiledb::FilterList::nfilters)
		.def("set_max_chunk_size", &tiledb::FilterList::set_max_chunk_size, py::arg("max_chunk_size"))
		;

}


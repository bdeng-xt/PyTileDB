#include "pybind_tiledb_cxx_object_iter.h" 

void init_tiledb_ObjectIter(pybind11::module& m) {
	pybind11::class_<tiledb::ObjectIter, std::shared_ptr<tiledb::ObjectIter> >(m,"ObjectIter")
		.def(py::init<tiledb::Context &,const std::string &>())
		.def("set_iter_policy", &tiledb::ObjectIter::set_iter_policy, py::arg("group"), py::arg("array"))
		.def("set_recursive", &tiledb::ObjectIter::set_recursive, py::arg("walk_order"))
		.def("set_non_recursive", &tiledb::ObjectIter::set_non_recursive)
		.def("begin", &tiledb::ObjectIter::begin)
		.def("end", &tiledb::ObjectIter::end)
//ignore_keywords 	int obj_getter( const char * path, tiledb_object_t type, void * data)
		;

}


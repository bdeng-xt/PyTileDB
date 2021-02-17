#include "pybind_tiledb_cxx_object.h" 

void init_tiledb_Object(pybind11::module& m) {
	pybind11::class_<tiledb::Object, std::shared_ptr<tiledb::Object> >(m,"Object")
//ignore_Type 	 Object( Type type, const std::string & uri)
		.def(py::init<tiledb_object_t,const std::string &>())
		.def(py::init<>())
		.def(py::init<const tiledb::Object>())
		.def(py::init<tiledb::Object &>())
//ignore_keywords 	tiledb::Object & operator=( const tiledb::Object &)
//ignore_keywords 	tiledb::Object & operator=( tiledb::Object & &)
		.def("to_str", &tiledb::Object::to_str)
//ignore_Type 	Object::Type type()
		.def("uri", &tiledb::Object::uri)
		.def_static("object", &tiledb::Object::object, py::arg("ctx"), py::arg("uri"))
		.def_static("remove", &tiledb::Object::remove, py::arg("ctx"), py::arg("uri"))
		.def_static("move", &tiledb::Object::move, py::arg("ctx"), py::arg("old_uri"), py::arg("new_uri"))
		;

}


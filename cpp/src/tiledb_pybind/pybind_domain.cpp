#include "pybind_domain.h" 

void init_tiledb_Domain(pybind11::module& m) {
	pybind11::class_<tiledb::Domain, std::shared_ptr<tiledb::Domain> >(m,"Domain")
		.def(py::init<const tiledb::Context &>())
//ignore_keywords 	 Domain( const tiledb::Context & ctx, tiledb_domain_t * domain)
		.def(py::init<const tiledb::Domain>())
		.def(py::init<tiledb::Domain &>())
//ignore_keywords 	Domain & operator=( const tiledb::Domain &)
//ignore_keywords 	Domain & operator=( tiledb::Domain & &)
//ignore_keywords 	uint64_t cell_num()
//ignore_keywords 	void dump( FILE * out)
		.def("type", &tiledb::Domain::type)
		.def("ndim", &tiledb::Domain::ndim)
		.def("dimensions", &tiledb::Domain::dimensions)
		.def("dimension", (tiledb::Dimension (tiledb::Domain::*)(unsigned) const)(&tiledb::Domain::dimension), py::arg("idx"))
		.def("dimension", (tiledb::Dimension (tiledb::Domain::*)(const std::string &) const)(&tiledb::Domain::dimension), py::arg("name"))
		.def("add_dimension", &tiledb::Domain::add_dimension, py::arg("d"))
		.def("add_int32_dimension", &tiledb::Domain::add_int32_dimension, py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def("add_int64_dimension", &tiledb::Domain::add_int64_dimension, py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def("add_uint64_dimension", &tiledb::Domain::add_uint64_dimension, py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def("add_double_dimension", &tiledb::Domain::add_double_dimension, py::arg("name"), py::arg("bound_lower"), py::arg("bound_upper"), py::arg("extent"))
		.def("add_string_dimension", &tiledb::Domain::add_string_dimension, py::arg("name"))
//ignore_templatefunction 	tiledb::Domain & add_dimensions( Args ... dims)
		.def("has_dimension", &tiledb::Domain::has_dimension, py::arg("name"))
//ignore_keywords 	std::shared_ptr<tiledb_domain_t > ptr()
		;

}


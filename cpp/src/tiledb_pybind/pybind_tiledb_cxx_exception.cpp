#include "pybind_tiledb_cxx_exception.h" 

void init_tiledb_TileDBError(pybind11::module& m) {
	pybind11::class_<tiledb::TileDBError, std::shared_ptr<tiledb::TileDBError> >(m,"TileDBError")
		.def(py::init<const std::string &>())
		;

}


void init_tiledb_TypeError(pybind11::module& m) {
	pybind11::class_<tiledb::TypeError, std::shared_ptr<tiledb::TypeError> >(m,"TypeError")
//ignore_Type 	 TypeError( const std::string & msg)
		;

}


void init_tiledb_SchemaMismatch(pybind11::module& m) {
	pybind11::class_<tiledb::SchemaMismatch, std::shared_ptr<tiledb::SchemaMismatch> >(m,"SchemaMismatch")
		.def(py::init<const std::string &>())
		;

}


void init_tiledb_AttributeError(pybind11::module& m) {
	pybind11::class_<tiledb::AttributeError, std::shared_ptr<tiledb::AttributeError> >(m,"AttributeError")
		.def(py::init<const std::string &>())
		;

}


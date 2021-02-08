#include "pybind_attribute.h" 

void init_tiledb_Attribute(pybind11::module& m) {
	pybind11::class_<tiledb::Attribute, std::shared_ptr<tiledb::Attribute> >(m,"Attribute")
//ignore_keywords 	 Attribute( const tiledb::Context & ctx, tiledb_attribute_t * attr)
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_datatype_t>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_datatype_t,const tiledb::FilterList &>())
		.def(py::init<const tiledb::Attribute>())
		.def(py::init<tiledb::Attribute &>())
//ignore_keywords 	tiledb::Attribute & operator=( const tiledb::Attribute &)
//ignore_keywords 	tiledb::Attribute & operator=( tiledb::Attribute & &)
		.def("name", &tiledb::Attribute::name)
		.def("type", &tiledb::Attribute::type)
		.def("cell_size", &tiledb::Attribute::cell_size)
		.def("cell_val_num", &tiledb::Attribute::cell_val_num)
		.def("set_cell_val_num", &tiledb::Attribute::set_cell_val_num, py::arg("num"))
		.def("variable_sized", &tiledb::Attribute::variable_sized)
		.def("filter_list", &tiledb::Attribute::filter_list)
		.def("set_filter_list", &tiledb::Attribute::set_filter_list, py::arg("filter_list"))
//ignore_keywords 	std::shared_ptr<tiledb_attribute_t > ptr()
//ignore_keywords 	void dump( FILE * out)
//ignore_templatefunction 	tiledb::Attribute create( const tiledb::Context & ctx, const std::string & name)
//ignore_templatefunction 	tiledb::Attribute create( const tiledb::Context & ctx, const std::string & name, const tiledb::FilterList & filter_list)
		.def_static("is_valid_intdatatype", &tiledb::Attribute::is_valid_intdatatype, py::arg("intdatatype"))
		.def_static("create_attribute", &tiledb::Attribute::create_attribute, py::arg("ctx"), py::arg("name"), py::arg("datatype"))
		;

}


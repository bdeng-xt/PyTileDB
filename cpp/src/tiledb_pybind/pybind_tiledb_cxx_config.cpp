#include "pybind_tiledb_cxx_config.h" 

void init_tiledb_Config(pybind11::module& m) {
	pybind11::class_<tiledb::Config, std::shared_ptr<tiledb::Config> >(m,"Config")
		.def(py::init<>())
		.def(py::init<const std::string &>())
//ignore_keywords 	 Config( tiledb_config_t * * config)
		.def("save_to_file", &tiledb::Config::save_to_file, py::arg("filename"))
//ignore_keywords 	std::shared_ptr<tiledb_config_t > ptr()
		.def("set", &tiledb::Config::set, py::arg("param"), py::arg("value"))
		.def("get", &tiledb::Config::get, py::arg("param"))
//ignore_keywords 	impl::ConfigProxy operator[]( const std::string & param)
		.def("unset", &tiledb::Config::unset, py::arg("param"))
//ignore_keywords 	impl::ConfigIter begin( const std::string & prefix)
//ignore_keywords 	impl::ConfigIter begin()
//ignore_keywords 	impl::ConfigIter end()
//ignore_keywords 	void free( tiledb_config_t * config)
		;

}


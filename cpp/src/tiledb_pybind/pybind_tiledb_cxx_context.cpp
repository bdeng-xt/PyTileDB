#include "pybind_tiledb_cxx_context.h" 

void init_tiledb_Context(pybind11::module& m) {
	pybind11::class_<tiledb::Context, std::shared_ptr<tiledb::Context> >(m,"Context")
		.def(py::init<>())
		.def(py::init<const tiledb::Config &>())
//ignore_keywords 	 Context( tiledb_ctx_t * ctx, bool own)
		.def("handle_error", &tiledb::Context::handle_error, py::arg("rc"))
//ignore_keywords 	std::shared_ptr<tiledb_ctx_t > ptr()
		.def("set_error_handler", &tiledb::Context::set_error_handler, py::arg("fn"))
		.def("config", &tiledb::Context::config)
		.def("is_supported_fs", &tiledb::Context::is_supported_fs, py::arg("fs"))
		.def("cancel_tasks", &tiledb::Context::cancel_tasks)
		.def("set_tag", &tiledb::Context::set_tag, py::arg("key"), py::arg("value"))
		.def_static("default_error_handler", &tiledb::Context::default_error_handler, py::arg("msg"))
		;

}


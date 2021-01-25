#include "pybind_vfs.h" 

void init_tiledb_VFS(pybind11::module& m) {
	pybind11::class_<tiledb::VFS, std::shared_ptr<tiledb::VFS> >(m,"VFS")
		.def(py::init<const tiledb::Context &>())
		.def(py::init<const tiledb::Context &,const tiledb::Config &>())
		.def(py::init<const tiledb::VFS>())
		.def(py::init<tiledb::VFS &>())
//ignore_keywords 	VFS & operator=( const tiledb::VFS &)
//ignore_keywords 	VFS & operator=( tiledb::VFS & &)
		.def("create_bucket", &tiledb::VFS::create_bucket, py::arg("uri"))
		.def("remove_bucket", &tiledb::VFS::remove_bucket, py::arg("uri"))
		.def("is_bucket", &tiledb::VFS::is_bucket, py::arg("uri"))
		.def("empty_bucket", &tiledb::VFS::empty_bucket, py::arg("bucket"))
		.def("is_empty_bucket", &tiledb::VFS::is_empty_bucket, py::arg("bucket"))
		.def("create_dir", &tiledb::VFS::create_dir, py::arg("uri"))
		.def("is_dir", &tiledb::VFS::is_dir, py::arg("uri"))
		.def("remove_dir", &tiledb::VFS::remove_dir, py::arg("uri"))
		.def("is_file", &tiledb::VFS::is_file, py::arg("uri"))
		.def("remove_file", &tiledb::VFS::remove_file, py::arg("uri"))
		.def("dir_size", &tiledb::VFS::dir_size, py::arg("uri"))
		.def("ls", &tiledb::VFS::ls, py::arg("uri"))
		.def("file_size", &tiledb::VFS::file_size, py::arg("uri"))
		.def("move_file", &tiledb::VFS::move_file, py::arg("old_uri"), py::arg("new_uri"))
		.def("move_dir", &tiledb::VFS::move_dir, py::arg("old_uri"), py::arg("new_uri"))
		.def("copy_file", &tiledb::VFS::copy_file, py::arg("old_uri"), py::arg("new_uri"))
		.def("touch", &tiledb::VFS::touch, py::arg("uri"))
		.def("context", &tiledb::VFS::context)
//ignore_keywords 	std::shared_ptr<tiledb_vfs_t > ptr()
		.def("config", &tiledb::VFS::config)
//ignore_keywords 	int ls_getter( const char * path, void * data)
		;

}


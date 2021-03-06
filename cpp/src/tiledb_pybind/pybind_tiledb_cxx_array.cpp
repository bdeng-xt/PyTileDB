#include "pybind_tiledb_cxx_array.h" 

void init_tiledb_Array(pybind11::module& m) {
	pybind11::class_<tiledb::Array, std::shared_ptr<tiledb::Array> >(m,"Array")
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t,tiledb_encryption_type_t,const void *,uint32_t>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t,tiledb_encryption_type_t,const std::string &>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t,uint64_t>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t,tiledb_encryption_type_t,const void *,uint32_t,uint64_t>())
		.def(py::init<const tiledb::Context &,const std::string &,tiledb_query_type_t,tiledb_encryption_type_t,const std::string &,uint64_t>())
//ignore_keywords 	 Array( const tiledb::Context & ctx, tiledb_array_t * carray, bool own)
		.def(py::init<const tiledb::Array>())
		.def(py::init<tiledb::Array &>())
//ignore_keywords 	tiledb::Array & operator=( const tiledb::Array &)
//ignore_keywords 	tiledb::Array & operator=( tiledb::Array & &)
//ignore_destructor 	 ~Array()
		.def("is_open", &tiledb::Array::is_open)
		.def("uri", &tiledb::Array::uri)
		.def("schema", &tiledb::Array::schema)
//ignore_keywords 	std::shared_ptr<tiledb_array_t > ptr()
		.def("open", (void (tiledb::Array::*)(tiledb_query_type_t))(&tiledb::Array::open), py::arg("query_type"))
//ignore_keywords 	void open( tiledb_query_type_t query_type, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length)
		.def("open", (void (tiledb::Array::*)(tiledb_query_type_t,tiledb_encryption_type_t,const std::string &))(&tiledb::Array::open), py::arg("query_type"), py::arg("encryption_type"), py::arg("encryption_key"))
		.def("open", (void (tiledb::Array::*)(tiledb_query_type_t,uint64_t))(&tiledb::Array::open), py::arg("query_type"), py::arg("timestamp"))
//ignore_keywords 	void open( tiledb_query_type_t query_type, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length, uint64_t timestamp)
		.def("open", (void (tiledb::Array::*)(tiledb_query_type_t,tiledb_encryption_type_t,const std::string &,uint64_t))(&tiledb::Array::open), py::arg("query_type"), py::arg("encryption_type"), py::arg("encryption_key"), py::arg("timestamp"))
		.def("reopen", &tiledb::Array::reopen)
		.def("reopen_at", &tiledb::Array::reopen_at, py::arg("timestamp"))
		.def("timestamp", &tiledb::Array::timestamp)
		.def("close", &tiledb::Array::close)
		.def_static("consolidate", static_cast< void (*)(const tiledb::Context &,const std::string &,tiledb::Config * const) >(&tiledb::Array::consolidate))
//ignore_keywords 	void consolidate( const tiledb::Context & ctx, const std::string & uri, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length, tiledb::Config * const config)
		.def_static("vacuum", &tiledb::Array::vacuum, py::arg("ctx"), py::arg("uri"), py::arg("config"))
		.def_static("consolidate", static_cast< void (*)(const tiledb::Context &,const std::string &,tiledb_encryption_type_t,const std::string &,tiledb::Config * const) >(&tiledb::Array::consolidate))
		.def_static("create", static_cast< void (*)(const std::string &,const tiledb::ArraySchema &) >(&tiledb::Array::create))
		.def_static("load_schema", static_cast< tiledb::ArraySchema (*)(const tiledb::Context &,const std::string &) >(&tiledb::Array::load_schema))
//ignore_keywords 	tiledb::ArraySchema load_schema( const tiledb::Context & ctx, const std::string & uri, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length)
//ignore_keywords 	void create( const std::string & uri, const tiledb::ArraySchema & schema, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length)
		.def_static("create", static_cast< void (*)(const std::string &,const tiledb::ArraySchema &,tiledb_encryption_type_t,const std::string &) >(&tiledb::Array::create))
		.def_static("encryption_type", &tiledb::Array::encryption_type, py::arg("ctx"), py::arg("array_uri"))
//ignore_keywords 	std::vector<std::pair<std::string, std::pair<T, T> > > non_empty_domain()
//ignore_keywords 	std::pair<T, T > non_empty_domain( unsigned idx)
//ignore_keywords 	std::pair<T, T > non_empty_domain( const std::string & name)
		.def("non_empty_domain_var", (std::pair<std::string, std::string > (tiledb::Array::*)(unsigned))(&tiledb::Array::non_empty_domain_var), py::arg("idx"))
		.def("non_empty_domain_var", (std::pair<std::string, std::string > (tiledb::Array::*)(const std::string &))(&tiledb::Array::non_empty_domain_var), py::arg("name"))
//ignore_keywords 	TILEDB_DEPRECATED std::unordered_map<std::string, std::pair<uint64_t, uint64_t> > max_buffer_elements( const std::vector<T> & subarray)
		.def("query_type", &tiledb::Array::query_type)
		.def_static("consolidate_metadata", static_cast< void (*)(const tiledb::Context &,const std::string &,tiledb::Config * const) >(&tiledb::Array::consolidate_metadata))
//ignore_keywords 	void consolidate_metadata( const tiledb::Context & ctx, const std::string & uri, tiledb_encryption_type_t encryption_type, const void * encryption_key, uint32_t key_length, tiledb::Config * const config)
		.def_static("consolidate_metadata", static_cast< void (*)(const tiledb::Context &,const std::string &,tiledb_encryption_type_t,const std::string &,tiledb::Config * const) >(&tiledb::Array::consolidate_metadata))
//ignore_keywords 	void put_metadata( const std::string & key, tiledb_datatype_t value_type, uint32_t value_num, const void * value)
		.def("delete_metadata", &tiledb::Array::delete_metadata, py::arg("key"))
//ignore_keywords 	void get_metadata( const std::string & key, tiledb_datatype_t * value_type, uint32_t * value_num, const void * * value)
		.def("has_metadata", &tiledb::Array::has_metadata, py::arg("key"), py::arg("value_type"))
		.def("metadata_num", &tiledb::Array::metadata_num)
//ignore_keywords 	void get_metadata_from_index( uint64_t index, std::string * key, tiledb_datatype_t * value_type, uint32_t * value_num, const void * * value)
		;

}


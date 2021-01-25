#include "pybind_tiledb_enum.h" 
void init__tiledb_query_type_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_query_type_t>(m,"tiledb_query_type_t")
		.value("TILEDB_READ", ::TILEDB_READ)
		.value("TILEDB_WRITE", ::TILEDB_WRITE)
		.export_values();

}

void init__tiledb_object_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_object_t>(m,"tiledb_object_t")
		.value("TILEDB_INVALID", ::TILEDB_INVALID)
		.value("TILEDB_GROUP", ::TILEDB_GROUP)
		.value("TILEDB_ARRAY", ::TILEDB_ARRAY)
		.export_values();

}

void init__tiledb_filesystem_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_filesystem_t>(m,"tiledb_filesystem_t")
		.value("TILEDB_HDFS", ::TILEDB_HDFS)
		.value("TILEDB_S3", ::TILEDB_S3)
		.value("TILEDB_AZURE", ::TILEDB_AZURE)
		.value("TILEDB_GCS", ::TILEDB_GCS)
		.export_values();

}

void init__tiledb_datatype_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_datatype_t>(m,"tiledb_datatype_t")
		.value("TILEDB_INT32", ::TILEDB_INT32)
		.value("TILEDB_INT64", ::TILEDB_INT64)
		.value("TILEDB_FLOAT32", ::TILEDB_FLOAT32)
		.value("TILEDB_FLOAT64", ::TILEDB_FLOAT64)
		.value("TILEDB_CHAR", ::TILEDB_CHAR)
		.value("TILEDB_INT8", ::TILEDB_INT8)
		.value("TILEDB_UINT8", ::TILEDB_UINT8)
		.value("TILEDB_INT16", ::TILEDB_INT16)
		.value("TILEDB_UINT16", ::TILEDB_UINT16)
		.value("TILEDB_UINT32", ::TILEDB_UINT32)
		.value("TILEDB_UINT64", ::TILEDB_UINT64)
		.value("TILEDB_STRING_ASCII", ::TILEDB_STRING_ASCII)
		.value("TILEDB_STRING_UTF8", ::TILEDB_STRING_UTF8)
		.value("TILEDB_STRING_UTF16", ::TILEDB_STRING_UTF16)
		.value("TILEDB_STRING_UTF32", ::TILEDB_STRING_UTF32)
		.value("TILEDB_STRING_UCS2", ::TILEDB_STRING_UCS2)
		.value("TILEDB_STRING_UCS4", ::TILEDB_STRING_UCS4)
		.value("TILEDB_ANY", ::TILEDB_ANY)
		.value("TILEDB_DATETIME_YEAR", ::TILEDB_DATETIME_YEAR)
		.value("TILEDB_DATETIME_MONTH", ::TILEDB_DATETIME_MONTH)
		.value("TILEDB_DATETIME_WEEK", ::TILEDB_DATETIME_WEEK)
		.value("TILEDB_DATETIME_DAY", ::TILEDB_DATETIME_DAY)
		.value("TILEDB_DATETIME_HR", ::TILEDB_DATETIME_HR)
		.value("TILEDB_DATETIME_MIN", ::TILEDB_DATETIME_MIN)
		.value("TILEDB_DATETIME_SEC", ::TILEDB_DATETIME_SEC)
		.value("TILEDB_DATETIME_MS", ::TILEDB_DATETIME_MS)
		.value("TILEDB_DATETIME_US", ::TILEDB_DATETIME_US)
		.value("TILEDB_DATETIME_NS", ::TILEDB_DATETIME_NS)
		.value("TILEDB_DATETIME_PS", ::TILEDB_DATETIME_PS)
		.value("TILEDB_DATETIME_FS", ::TILEDB_DATETIME_FS)
		.value("TILEDB_DATETIME_AS", ::TILEDB_DATETIME_AS)
		.export_values();

}

void init__tiledb_array_type_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_array_type_t>(m,"tiledb_array_type_t")
		.value("TILEDB_DENSE", ::TILEDB_DENSE)
		.value("TILEDB_SPARSE", ::TILEDB_SPARSE)
		.export_values();

}

void init__tiledb_layout_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_layout_t>(m,"tiledb_layout_t")
		.value("TILEDB_ROW_MAJOR", ::TILEDB_ROW_MAJOR)
		.value("TILEDB_COL_MAJOR", ::TILEDB_COL_MAJOR)
		.value("TILEDB_GLOBAL_ORDER", ::TILEDB_GLOBAL_ORDER)
		.value("TILEDB_UNORDERED", ::TILEDB_UNORDERED)
		.export_values();

}

void init__tiledb_filter_type_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_filter_type_t>(m,"tiledb_filter_type_t")
		.value("TILEDB_FILTER_NONE", ::TILEDB_FILTER_NONE)
		.value("TILEDB_FILTER_GZIP", ::TILEDB_FILTER_GZIP)
		.value("TILEDB_FILTER_ZSTD", ::TILEDB_FILTER_ZSTD)
		.value("TILEDB_FILTER_LZ4", ::TILEDB_FILTER_LZ4)
		.value("TILEDB_FILTER_RLE", ::TILEDB_FILTER_RLE)
		.value("TILEDB_FILTER_BZIP2", ::TILEDB_FILTER_BZIP2)
		.value("TILEDB_FILTER_DOUBLE_DELTA", ::TILEDB_FILTER_DOUBLE_DELTA)
		.value("TILEDB_FILTER_BIT_WIDTH_REDUCTION", ::TILEDB_FILTER_BIT_WIDTH_REDUCTION)
		.value("TILEDB_FILTER_BITSHUFFLE", ::TILEDB_FILTER_BITSHUFFLE)
		.value("TILEDB_FILTER_BYTESHUFFLE", ::TILEDB_FILTER_BYTESHUFFLE)
		.value("TILEDB_FILTER_POSITIVE_DELTA", ::TILEDB_FILTER_POSITIVE_DELTA)
		.value("TILEDB_FILTER_CHECKSUM_MD5", ::TILEDB_FILTER_CHECKSUM_MD5)
		.value("TILEDB_FILTER_CHECKSUM_SHA256", ::TILEDB_FILTER_CHECKSUM_SHA256)
		.export_values();

}

void init__tiledb_filter_option_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_filter_option_t>(m,"tiledb_filter_option_t")
		.value("TILEDB_COMPRESSION_LEVEL", ::TILEDB_COMPRESSION_LEVEL)
		.value("TILEDB_BIT_WIDTH_MAX_WINDOW", ::TILEDB_BIT_WIDTH_MAX_WINDOW)
		.value("TILEDB_POSITIVE_DELTA_MAX_WINDOW", ::TILEDB_POSITIVE_DELTA_MAX_WINDOW)
		.export_values();

}

void init__tiledb_encryption_type_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_encryption_type_t>(m,"tiledb_encryption_type_t")
		.value("TILEDB_NO_ENCRYPTION", ::TILEDB_NO_ENCRYPTION)
		.value("TILEDB_AES_256_GCM", ::TILEDB_AES_256_GCM)
		.export_values();

}

void init__tiledb_query_status_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_query_status_t>(m,"tiledb_query_status_t")
		.value("TILEDB_FAILED", ::TILEDB_FAILED)
		.value("TILEDB_COMPLETED", ::TILEDB_COMPLETED)
		.value("TILEDB_INPROGRESS", ::TILEDB_INPROGRESS)
		.value("TILEDB_INCOMPLETE", ::TILEDB_INCOMPLETE)
		.value("TILEDB_UNINITIALIZED", ::TILEDB_UNINITIALIZED)
		.export_values();

}

void init__tiledb_serialization_type_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_serialization_type_t>(m,"tiledb_serialization_type_t")
		.value("TILEDB_JSON", ::TILEDB_JSON)
		.value("TILEDB_CAPNP", ::TILEDB_CAPNP)
		.export_values();

}

void init__tiledb_walk_order_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_walk_order_t>(m,"tiledb_walk_order_t")
		.value("TILEDB_PREORDER", ::TILEDB_PREORDER)
		.value("TILEDB_POSTORDER", ::TILEDB_POSTORDER)
		.export_values();

}

void init__tiledb_vfs_mode_t(pybind11::module& m) {
	pybind11::enum_<::tiledb_vfs_mode_t>(m,"tiledb_vfs_mode_t")
		.value("TILEDB_VFS_READ", ::TILEDB_VFS_READ)
		.value("TILEDB_VFS_WRITE", ::TILEDB_VFS_WRITE)
		.value("TILEDB_VFS_APPEND", ::TILEDB_VFS_APPEND)
		.export_values();

}


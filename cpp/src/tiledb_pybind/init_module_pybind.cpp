#include "common_include.h" 

#include "init_module_common.h"

//////

#include "pybind_tiledb_cxx.h" 

#include "pybind_tiledb_cxx_array.h" 

#include "pybind_tiledb_cxx_array_schema.h" 

#include "pybind_tiledb_cxx_array_util.h" 

#include "pybind_tiledb_cxx_attribute.h" 

#include "pybind_tiledb_cxx_column.h" 

#include "pybind_tiledb_cxx_config.h" 

#include "pybind_tiledb_cxx_context.h" 

#include "pybind_tiledb_cxx_core_interface.h" 

#include "pybind_tiledb_cxx_dimension.h" 

#include "pybind_tiledb_cxx_domain.h" 

#include "pybind_tiledb_cxx_exception.h" 

#include "pybind_tiledb_cxx_filter.h" 

#include "pybind_tiledb_cxx_filter_list.h" 

#include "pybind_tiledb_cxx_group.h" 

#include "pybind_tiledb_cxx_object.h" 

#include "pybind_tiledb_cxx_object_iter.h" 

#include "pybind_tiledb_cxx_query.h" 

#include "pybind_tiledb_cxx_stats.h" 

#include "pybind_tiledb_cxx_string_util.h" 

#include "pybind_tiledb_cxx_type.h" 

#include "pybind_tiledb_cxx_utils.h" 

#include "pybind_tiledb_cxx_version.h" 

#include "pybind_tiledb_cxx_vfs.h" 

#include "pybind_tiledb_enum.h" 
////////////
#ifdef PYTHON_VERSION_2
PYBIND11_MODULE(pytiledb2, m)
#else
PYBIND11_MODULE(pytiledb, m)
#endif
{
	init_common(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_array.h
	init_tiledb_Array(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_array_schema.h
	init_tiledb_ArraySchema(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_array_util.h
	init_tiledb_ArrayUtil(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_attribute.h
	init_tiledb_Attribute(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_column.h
	init_tiledb_ColumnData(m);
	init_tiledb_StringColumnData(m);
	init_tiledb_ColumnDataMap(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_config.h
	init_tiledb_Config(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_context.h
	init_tiledb_Context(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_core_interface.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_dimension.h
	init_tiledb_Dimension(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_domain.h
	init_tiledb_Domain(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_exception.h
	init_tiledb_TileDBError(m);
	init_tiledb_TypeError(m);
	init_tiledb_SchemaMismatch(m);
	init_tiledb_AttributeError(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_filter.h
	init_tiledb_Filter(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_filter_list.h
	init_tiledb_FilterList(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_group.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_object.h
	init_tiledb_Object(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_object_iter.h
	init_tiledb_ObjectIter(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_query.h
	init_tiledb_Query(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_stats.h
	init_tiledb_Stats(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_string_util.h
	init_tiledb_StringUtil(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_type.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_utils.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_version.h

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_cxx_vfs.h
	init_tiledb_VFS(m);

//file:../../../bdeng-xt/PyTileDB/cpp/src/tiledb/cxx_api/tiledb_enum.h
	init__tiledb_query_type_t(m);
	init__tiledb_object_t(m);
	init__tiledb_filesystem_t(m);
	init__tiledb_datatype_t(m);
	init__tiledb_array_type_t(m);
	init__tiledb_layout_t(m);
	init__tiledb_filter_type_t(m);
	init__tiledb_filter_option_t(m);
	init__tiledb_encryption_type_t(m);
	init__tiledb_query_status_t(m);
	init__tiledb_serialization_type_t(m);
	init__tiledb_walk_order_t(m);
	init__tiledb_vfs_mode_t(m);

}//PYBIND11_MODULE(pytiledb, m)

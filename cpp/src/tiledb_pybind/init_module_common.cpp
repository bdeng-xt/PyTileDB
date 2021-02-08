#include "init_module_common.h"

#include "array_util.h"
void init_common(pybind11::module& m)
{
	std::string version_str = tiledb::ArrayUtil::get_version();
	m.attr("__version__") = version_str; //version 
}
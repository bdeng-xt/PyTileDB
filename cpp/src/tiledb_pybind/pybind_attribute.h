#pragma once
#ifndef TILEDB_PYBIND_ATTRIBUTE_H
#define TILEDB_PYBIND_ATTRIBUTE_H

#include "common_include.h" 
#include "init_module_common.h"


#include "attribute.h"

void init_tiledb_Attribute(pybind11::module& m);


#endif
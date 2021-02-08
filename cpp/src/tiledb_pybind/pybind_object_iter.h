#pragma once
#ifndef TILEDB_PYBIND_OBJECT_ITER_H
#define TILEDB_PYBIND_OBJECT_ITER_H

#include "common_include.h" 
#include "init_module_common.h"


#include "object_iter.h"

void init_tiledb_ObjectIter(pybind11::module& m);


#endif
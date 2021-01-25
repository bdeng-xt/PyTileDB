#pragma once
#ifndef TILEDB_PYBIND_EXCEPTION_H
#define TILEDB_PYBIND_EXCEPTION_H

#include "common_include.h" 


#include "exception.h"

void init_tiledb_TileDBError(pybind11::module& m);

void init_tiledb_TypeError(pybind11::module& m);

void init_tiledb_SchemaMismatch(pybind11::module& m);

void init_tiledb_AttributeError(pybind11::module& m);


#endif
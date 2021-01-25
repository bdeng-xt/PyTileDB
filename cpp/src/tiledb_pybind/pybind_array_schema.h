#pragma once
#ifndef TILEDB_PYBIND_ARRAY_SCHEMA_H
#define TILEDB_PYBIND_ARRAY_SCHEMA_H

#include "common_include.h" 


#include "array_schema.h"

void init_tiledb_ArraySchema(pybind11::module& m);


#endif
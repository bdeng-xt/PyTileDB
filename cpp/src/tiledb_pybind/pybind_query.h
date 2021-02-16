#pragma once
#ifndef TILEDB_PYBIND_QUERY_H
#define TILEDB_PYBIND_QUERY_H

#include "common_include.h" 


#include "query.h"

void init_tiledb_Query(pybind11::module& m);


#endif
#pragma once
#ifndef TILEDB_PYBIND_STATS_H
#define TILEDB_PYBIND_STATS_H

#include "common_include.h" 
#include "init_module_common.h"


#include "stats.h"

void init_tiledb_Stats(pybind11::module& m);


#endif
#pragma once
#ifndef TILEDB_PYBIND_CONFIG_H
#define TILEDB_PYBIND_CONFIG_H

#include "common_include.h" 
#include "init_module_common.h"


#include "config.h"

void init_tiledb_Config(pybind11::module& m);


#endif
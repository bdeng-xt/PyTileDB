#pragma once
#ifndef TILEDB_PYBIND_DOMAIN_H
#define TILEDB_PYBIND_DOMAIN_H

#include "common_include.h" 
#include "init_module_common.h"


#include "domain.h"

void init_tiledb_Domain(pybind11::module& m);


#endif
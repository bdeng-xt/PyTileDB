#pragma once
#ifndef TILEDB_PYBIND_VFS_H
#define TILEDB_PYBIND_VFS_H

#include "common_include.h" 


#include "vfs.h"

void init_tiledb_VFS(pybind11::module& m);


#endif
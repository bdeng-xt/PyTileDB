#pragma once
#ifndef INIT_MODULE_COMMON_H
#define INIT_MODULE_COMMON_H

/**
* \file init_module_common.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide customized wrapper(not automatically).
*
* \description
*	All pybind_* files are generated automatically. This component provides some customized initialization. 
*/

#include "common_include.h" 

 

void init_common(pybind11::module& m);


#endif
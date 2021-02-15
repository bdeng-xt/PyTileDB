#
# CMakeLists.txt
#
#
# setup
cmake_minimum_required(VERSION 3.17)
 
project(PyTileDB)

# C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Release build by default
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif()

# installation prefix
if (OVERRIDE_INSTALL_PREFIX)
  set(PREFIX_REL_PATH "${CMAKE_SOURCE_DIR}/../dist")
  get_filename_component(DEFAULT_PREFIX "${PREFIX_REL_PATH}" ABSOLUTE)
  set(CMAKE_INSTALL_PREFIX "${DEFAULT_PREFIX}" CACHE PATH "Default install prefix" FORCE)
  message(STATUS "Using default install prefix ${CMAKE_INSTALL_PREFIX}. To control CMAKE_INSTALL_PREFIX, set OVERRIDE_INSTALL_PREFIX=OFF")
endif()

# compiler flags
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
if(BUILD_TYPE STREQUAL "RELEASE")
  add_compile_options(-DNEBUG)
endif()

if(BUILD_TYPE STREQUAL "DEBUG")
  add_compile_options(-DDEBUG )
endif()

 
######################################
# Regular Build
######################################
# Enable testing
enable_testing()

# src
add_subdirectory(src)

# test
#add_subdirectory(test)


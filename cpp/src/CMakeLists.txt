message(STATUS "Starting PyTileDB build")

#############################
# pybind11
#############################
include(FetchContent)
FetchContent_Declare(
  pybind11_sources
  GIT_REPOSITORY https://github.com/pybind/pybind11.git 
  GIT_TAG v2.6.1
)
FetchContent_GetProperties(pybind11_sources)

if(NOT pybind11_sources_POPULATED)
  FetchContent_Populate(pybind11_sources)
  message(STATUS "pybind11 source dir:${pybind11_sources_SOURCE_DIR}")
  add_subdirectory(
    ${pybind11_sources_SOURCE_DIR}
    ${pybind11_sources_BINARY_DIR}
  )
endif()

###########################
# tiledb
############################
if (WIN32) # Windows
  SET(TILEDB_DOWNLOAD_URL "https://github.com/TileDB-Inc/TileDB/releases/download/2.0.7/tiledb-windows-2.0.7-2058d3d.zip")
  SET(TILEDB_DOWNLOAD_SHA1 "4E3BEED60F2F29B31DDA04CAA21DDE22B96B77B9")
elseif(APPLE) # OSX
  SET(TILEDB_DOWNLOAD_URL "https://github.com/TileDB-Inc/TileDB/releases/download/2.0.7/tiledb-macos-2.0.7-2058d3d.tar.gz")
  SET(TILEDB_DOWNLOAD_SHA1 "B5CF25FC57B89009D3F5E21AC902C7642BA295E6")
else() # Linux
  SET(TILEDB_DOWNLOAD_URL "https://github.com/TileDB-Inc/TileDB/releases/download/2.0.7/tiledb-linux-2.0.7-2058d3d.tar.gz")
  SET(TILEDB_DOWNLOAD_SHA1 "556CCD6265A9F62884A8F798753625D7352ACCD5")
endif()

FetchContent_Declare(
  tiledb_prebuilt
  URL ${TILEDB_DOWNLOAD_URL}
  URL_HASH SHA1=${TILEDB_DOWNLOAD_SHA1}
)
FetchContent_GetProperties(tiledb_prebuilt)

if(NOT tiledb_prebuilt_POPULATED)
  FetchContent_Populate(tiledb_prebuilt)

  message(STATUS "tiledb_prebuilt_SOURCE_DIR:${tiledb_prebuilt_SOURCE_DIR}")
  message(STATUS "tiledb_prebuilt_BINARY_DIR:${tiledb_prebuilt_BINARY_DIR}")
#  add_subdirectory(
#    ${tiledb_prebuilt_SOURCE_DIR}
#    ${tiledb_prebuilt_BINARY_DIR}
#  )
endif()
include(${tiledb_prebuilt_SOURCE_DIR}/lib/cmake/TileDB/TileDBConfig.cmake)
include(${tiledb_prebuilt_SOURCE_DIR}/lib/cmake/TileDB/TileDBTargets.cmake)
include(${tiledb_prebuilt_SOURCE_DIR}/lib/cmake/TileDB/TileDBTargets-release.cmake)

###############################
# zlib  
###############################
FetchContent_Declare(
    zlib
    GIT_REPOSITORY "https://github.com/madler/zlib.git"
    GIT_TAG "v1.2.11"
)
FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)
    message(STATUS "zlib_SOURCE_DIR:${zlib_SOURCE_DIR}")
    message(STATUS "zlib_BINARY_DIR:${zlib_BINARY_DIR}")
    add_subdirectory(
      ${zlib_SOURCE_DIR} 
      ${zlib_BINARY_DIR}
      )
endif()



###############################
# python
###############################
# find python
find_package(PythonInterp REQUIRED)
# find python lib
find_package(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)

# find pyarrow
execute_process(
  COMMAND
    ${PYTHON_EXECUTABLE} "-c" "import re,pyarrow; print(re.compile('__init__.py*').sub('',pyarrow.__file__))"
  RESULT_VARIABLE _pyarrow_status
  OUTPUT_VARIABLE _pyarrow_location
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT ${_pyarrow_status})
  set(PyArrow ${_pyarrow_location} CACHE STRING "Location of PyArrow")
  message(STATUS "location of pyarrow:${_pyarrow_location}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pyarrow
  FOUND_VAR PYARROW_FOUND
  REQUIRED_VARS PyArrow 
  VERSION_VAR _pyarrow_version
)





##################################
# Common Object library
##################################
set(TILEDB_CXX_API_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/array.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/array_schema.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/array_util.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/array_util.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/attribute.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/column.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/column.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/config.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/context.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/core_interface.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/deleter.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/dimension.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/domain.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/exception.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/filter.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/filter_list.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/group.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/json.hpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/object.h  
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/object_iter.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/query.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/schema_base.h     
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/stats.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/string_util.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/string_util.cc 
 # ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/tiledb 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/tiledb_enum.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/type.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/utils.h  
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/version.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api/vfs.h  
)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB_RECURSE TILEDB_PYBIND_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tiledb_pybind/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tiledb_pybind/*.h)
else()
    file(GLOB TILEDB_PYBIND_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tiledb_pybind/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tiledb_pybind/*.h )
endif()

########################
# pytiledb library
#######################
 

add_library(pytiledb
  SHARED
  ${TILEDB_CXX_API_SOURCES}
  ${TILEDB_PYBIND_SOURCES}
)

 

target_include_directories(pytiledb
  PUBLIC
    ${PYTHON_INCLUDE_DIRS}
    ${pybind11_sources_SOURCE_DIR}/include
    ${zlib_SOURCE_DIR}/include 
    ${_pyarrow_location}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tiledb/cxx_api
    ${CMAKE_CURRENT_SOURCE_DIR}/tiledb_pybind

)

target_link_directories(pytiledb
  PUBLIC
    ${PYTHON_LIBRARY}
    ${_pyarrow_location}
    pybind11::module
    ${tiledb_prebuilt_SOURCE_DIR}/lib
    ${tiledb_prebuilt_SOURCE_DIR}/bin
)

 

target_link_libraries(pytiledb
  PUBLIC 
    ${PYTHON_LIBRARIES}
    TileDB::tiledb_shared
)

if(UNIX)

  add_compile_options(
    "HAVE_PYCONFIG"
    "-D_GLIBCXX_USE_NANOSLEEP"
    "-D_THREAD_SAFE"
    "-D_XOPEN_SOURCE_EXTENEDED"
    "-D_GCC"
    "-D_PROTOTYPES"
    "-D_DRTP_V4"
    "-DLINUX"
    "-D_POSIX_THREADS"      
  )

  set_target_properties(pytiledb
    PROPERTIES
      PREFIX ""
      SUFFIX ".so"
  )
  target_link_libraries(pytiledb
    PUBLIC
      pthread
      libarrow.so.200
      libarrow_python.so.200
  )
endif()

if(WIN32)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}
  "HAVE_PYCONFIG"
    "WIN32"
    "_WIN32"
    "WIN32_LEAN_AND_MEAN"
    "_WIN64" 
    "/wd\"4996\""
    "/wd\"4819\""
    "/wd\"4251\""
    "/wd\"4005\"" 
    "/wd\"4275\"" 
    "/wd\"4800\""     
  )
  set_target_properties(pytiledb
    PROPERTIES
      PREFIX ""
      SUFFIX ".pyd"
  )
  target_link_libraries(pytiledb
    PUBLIC
      arrow,
      arrow_python
  )  

endif()


 
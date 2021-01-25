# PyTileDB
A customized python wrapper to the TileDB. This is NOT the official wrapper.

#Changed made to c_api
tiledb_enum.h ---> change macro concatenation to normal enum definition, also added "#pragma once"
tiledb.h  ---> comment all enum definition and include "tiledb_enum.h"

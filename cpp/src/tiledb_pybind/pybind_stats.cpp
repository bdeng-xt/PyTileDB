#include "pybind_stats.h" 

void init_tiledb_Stats(pybind11::module& m) {
	pybind11::class_<tiledb::Stats, std::shared_ptr<tiledb::Stats> >(m,"Stats")
		.def_static("enable", &tiledb::Stats::enable)
		.def_static("disable", &tiledb::Stats::disable)
		.def_static("reset", &tiledb::Stats::reset)
//ignore_keywords 	void dump( FILE * out)
		.def_static("dump", static_cast< void (*)(std::string *) >(&tiledb::Stats::dump))
//ignore_keywords 	void raw_dump( FILE * out)
		.def_static("raw_dump", static_cast< void (*)(std::string *) >(&tiledb::Stats::raw_dump))
		;

}


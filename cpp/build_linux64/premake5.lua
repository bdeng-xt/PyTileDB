workspace "pytiledb" --solution "xtcommon"
	configurations {"Release"} --,"Debug"}
	platforms {"linux64"}--,"win64"}--{"linux64","win32"}
	filter "platforms:linux64"
  		system "linux"
		kind "SharedLib"
		architecture "x64"
--    platforms {"win64"}
--    filter "platforms:win64"
--		system "windows"
--        kind "SharedLib"
--        architecture "x64"
----------------------------
		excludes
		{

		}
		includedirs
		{
			"../src/tiledb/cxx_api",
			"../src/tiledb_pybind",
 
		}
		libdirs
		{
		}
 

	


--------------------------------------------------------------------------------------


	if _ACTION=="gmake" or _ACTION=="codeblocks" or _ACTION=="codelite" then
 
		includedirs
		{
			"./",
			"./include",
			"../include",
			"/opt/boost_1_68_0",
			"/usr/include",
			"/usr/local/include",
            "/opt/anaconda3/include",
			"/opt/anaconda3/include/python3.7m",
			"/opt/anaconda3/lib/python3.7/site-packages/pyarrow/include"

		}
		libdirs
		{
			"./",
--			"../../lib/linux64",
			"/usr/lib64",
			"/usr/local/lib",
            "/usr/local/lib64",
--            "/usr/lib64/python2.7",
			"/opt/anaconda3/lib",
			"/opt/anaconda3/lib/python3.7/site-packages/pyarrow"
					
		}
 
--		defines {"BOOST_ALL_NO_LIB"}
 
	
		flags
		{}
		buildoptions {"-m64", "-std=gnu++0x", "-fPIC","-D_GLIBCXX_USE_NANOSLEEP", "-D_THREAD_SAFE","-D_XOPEN_SOURCE_EXTENEDED","-D_GCC","-D_PROTOTYPES","-D_DRTP_V4","-DLINUX","-D_POSIX_THREADS"}
		
		linkoptions {"-m64", "-std=gnu++0x", "-fPIC",  "-D_GLIBCXX_USE_NANOSLEEP", "-D_THREAD_SAFE","-D_XOPEN_SOURCE_EXTENEDED","-D_GCC","-D_PROTOTYPES","-D_DRTP_V4","-DLINUX","-D_POSIX_THREADS", "-lm", "-lrt", "-lpthread", "-lstdc++", "-ldl"}		

 
		
	end --if _ACTION=="gmake" or _ACTION=="codeblocks" or _ACTION=="codelite" then
	
	if _ACTION=="vs2012" or _ACTION=="vs2013" or _ACTION=="vs2015" or _ACTION=="vs2017" then
 
		includedirs
		{
			"./",
			"./include",
			"../include",
			"C:\\Dev\\boost_1_68_0",
			"C:\\Dev\\Python\\include",
			"C:\\Dev\\Python\\Lib\\site-packages\\pyarrow\\include"
		}
		libdirs
		{
			"./",
			"../../lib/win64"
 
		}
--		defines {"WIN32","_WIN32","WIN32_LEAN_AND_MEAN","XT_COMMON_API_EXPORTS","_DLL","BOOST_DYN_LINK","BOOST_LIB_NAME","BOOST_ALL_NO_LIB"}
		defines {"WIN32","_WIN32","WIN32_LEAN_AND_MEAN" }


    --
--        defines { "BOOST_ALL_NO_LIB" } --, "SWIG"}
       
 
        defines {"_WIN64"}    

 
		buildoptions
		{
			"/wd\"4996\"","/wd\"4819\"","/wd\"4251\"","/wd\"4005\"" ,"/wd\"4275\"" ,"/wd\"4800\"" 
		}
        linkoptions {"/NXCOMPAT:NO"}
     
--        buildoptions
--        {
--            "/std:c++17"
--        }        
		
	end --if _ACTION=="vs2012" or _ACTION=="vs2013" or _ACTION=="vs2015" or _ACTION=="vs2017" then
	
 --------------------------------------------------------------------------------------------------------- 
		
 --------------------------------------------------------------------------------------------------------- 
-------------			
 	project "pytiledb"
		kind "SharedLib"
--		kind "StaticLib"
		language "C++"
--
		includedirs
		{
			"../../../pybind11-2.6.1/include",

		}

		files
		{   
--			"../../cpp/src/xtboost/**.cpp",   
			"../src/tiledb_pybind/*.cpp"
		}		
		excludes
		{
--			"../../cpp/src/xtboost/boost_python.cpp",
		}		

		if _ACTION=="gmake" or _ACTION=="codeblocks" or _ACTION=="codelite" then
			targetdir "../../"
--            platforms {"x64"}
			targetname "pytiledb"
			targetprefix ""
			linkoptions {"-lpython3.7m"} --{"-lpython2.7"} --,"-lboost_python"}
			linkoptions {"-l :libarrow.so.200", "-l :libarrow_python.so.200"}
            linkoptions {"-l :libtiledb.so.2.1"}
 			defines {"HAVE_PYCONFIG"}

		end--if _ACTION=="gmake" or _ACTION=="codeblocks" or _ACTION=="codelite" then
		if _ACTION=="vs2012" or _ACTION=="vs2013" or _ACTION=="vs2015" or _ACTION=="vs2017"  then
			targetdir "../../"
			targetname "pytiledb"
			targetextension ".pyd"
 --           platforms {"x64"}
 --     defines {"_SSIZE_T_DEFINED"}
--			targetextension ".pyd"
            defines {"HAVE_PYCONFIG"}
			includedirs
			{
				"C:\\Dev\\Python\\include"
			}
			libdirs
			{
		      	"../../lib/win64",
--				"../../../xtdeploy/lib/win64"
			}
			buildoptions
			{
				"/bigobj"
			}
 
			links {"python37"}
			links {"arrow","arrow_python"}
            links {"tiledb"}
--            defines {"__TBB_NO_IMPLICIT_LINKAGE"}
 

		end--		
 
        configuration "Release"
            if _ACTION=="gmake" or _ACTION=="codeblocks" or _ACTION=="codelite" then
--                platforms {"x64"}
                flags {"Optimize"}   
                defines {"NDEBUG"}
            end
            if _ACTION=="vs2012" or _ACTION=="vs2013" or _ACTION=="vs2015" or _ACTION=="vs2017"  then
--               platforms {"x64"}
--              flags {"Optimize","StaticRuntime"}
                defines {"_MT"}
            end

----------------------		

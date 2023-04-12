CMAKE_MINIMUM_REQUIRED(VERSION 3.18)


##################################################
#                    Options                     #
##################################################

set(PBNI_DIR "C:/Program Files (x86)/Appeon/PowerBuilder 17.0/SDK/PBNI" CACHE PATH "PATH of PowerBuilder Native Interface SDK")
set(PBNI_INCLUDE_DIR "${PBNI_DIR}/include" CACHE PATH "PowerBuilder Native Interface header files location")
set(PBNI_LIBRARY "${PBNI_DIR}/lib/pbni.lib" CACHE FILEPATH "PowerBuilder Native Interface library for release target")

option(PBNI_USE_MULTITHREADED_RUNTIME "Whether to set the MTD option when building" OFF)

##################################################
#                 PBNI Framework                 #
##################################################

project(lib.cpp.base.pbni-framework VERSION 1.0.0 LANGUAGES CXX)

# Check for 32 bit
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
	message(FATAL_ERROR "Powerbuilder runs on 32 bits, choose a 32 bit plattform using '-A Win32'")
endif()


set(src
	src/Framework.cpp
	src/Framework.h
	src/Errors.h
	src/AcquiredValue.h
	src/PBEntry.cpp
)

set(descriptions
	src/MethodDescription.h
	src/ClassDescription.h
)

set(types
	src/PBTypes.h
	src/PBArray.h
	src/PBBlob.cpp
	src/PBBlob.h
	src/PBDateTimes.cpp
	src/PBDateTimes.h
	src/PBNumbers.h
	src/PBNumbers.cpp
	src/PBObjects.h
	src/PBString.cpp
	src/PBString.h
)

set(headers ${src})
list(APPEND headers ${descriptions})
list(APPEND headers ${types})
list(FILTER headers INCLUDE REGEX "\.h$")

add_library(libPBNIFramework STATIC
	${src}
	${descriptions}
	${types}
)
source_group("Source Files" FILES ${src})
source_group("Source Files/Descriptions" FILES ${descriptions})
source_group("Source Files/Types" FILES ${types})

target_precompile_headers(libPBNIFramework PUBLIC ${headers})


target_compile_features(libPBNIFramework PUBLIC cxx_std_20)

# To be able to use __VA_OPT__
target_compile_options(libPBNIFramework PUBLIC /Zc:preprocessor)

if(PBNI_USE_MULTITHREADED_RUNTIME) 
	set_target_properties(libPBNIFramework
	PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()

target_compile_definitions(libPBNIFramework
PUBLIC
	-DUNICODE
	-D_UNICODE
	-DWIN32_LEAN_AND_MEAN
)

# Visual C++ Linker doesn't include Functions from a Static Library in a DLL, even if they are declared using dllexport
# This forces the Linker to include the Functions, and export them if they have dllexport.
target_link_options(libPBNIFramework
INTERFACE
	/INCLUDE:"_PBX_GetDescription@0"
	/INCLUDE:"_PBX_CreateNonVisualObject@16"
)

find_package(Boost
REQUIRED
	stacktrace_windbg
)

target_link_libraries(libPBNIFramework
INTERFACE
	${PBNI_LIBRARY}
	
PUBLIC
	Boost::stacktrace_windbg
)

target_include_directories(libPBNIFramework
INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/src

PUBLIC
	${PBNI_INCLUDE_DIR}

	# Header only libraries
	Boost::utility
	Boost::multiprecision
)

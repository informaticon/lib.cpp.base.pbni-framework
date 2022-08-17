CMAKE_MINIMUM_REQUIRED(VERSION 3.18)


##################################################
#                 PBNI Framework                 #
##################################################

# Check for 32 bit
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
	message(FATAL_ERROR "Powerbuilder runs on 32 bits, choose a 32 bit plattform using '-A Win32'")
endif()

project(lib.cpp.base.pbni-framework VERSION 1.0.0 LANGUAGES CXX)

add_library(libPBNIFramework STATIC
	src/Framework.cpp
	src/Framework.h
	src/Errors.h
	src/AcquiredValue.h
	src/PBEntry.cpp

	src/MethodDescription.h
	src/ClassDescription.h

	src/PBTypes.h
	src/PBArray.h
	src/PBBlob.cpp
	src/PBBlob.h
	src/PBDateTimes.cpp
	src/PBDateTimes.h
	src/PBNumbers.h
	src/PBObjects.h
	src/PBString.cpp
	src/PBString.h
)

source_group(src
FILES
	src/Framework.cpp
	src/Framework.h
	src/Errors.h
	src/AcquiredValue.h
	src/PBEntry.cpp
)

source_group(src/Descriptions
FILES
	src/MethodDescription.h
	src/ClassDescription.h
)

source_group(src/Types
FILES
	src/PBTypes.h
	src/PBArray.h
	src/PBBlob.cpp
	src/PBBlob.h
	src/PBDateTimes.cpp
	src/PBDateTimes.h
	src/PBNumbers.h
	src/PBObjects.h
	src/PBString.cpp
	src/PBString.h
)


target_compile_features(libPBNIFramework PUBLIC cxx_std_20)

# To be able to use __VA_OPT__
target_compile_options(libPBNIFramework PUBLIC /Zc:preprocessor)

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
	/INCLUDE:_PBX_GetDescription@0
	/INCLUDE:_PBX_CreateNonVisualObject@16
)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(BOOST_STACKTRACE_ENABLE_NOOP OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_noop")
set(BOOST_STACKTRACE_ENABLE_BACKTRACE OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_backtrace")
set(BOOST_STACKTRACE_ENABLE_ADDR2LINE OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_addr2line")
set(BOOST_STACKTRACE_ENABLE_BASIC OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_basic")
set(BOOST_STACKTRACE_ENABLE_WINDBG ON CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_windbg")
set(BOOST_STACKTRACE_ENABLE_WINDBG_CACHED OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_windbg_cached")


add_subdirectory(extern)

target_link_libraries(libPBNIFramework
PUBLIC
	Boost::utility
	Boost::multiprecision
	Boost::stacktrace_windbg

INTERFACE
	${PBNI_LIBRARY}
)

target_include_directories(libPBNIFramework
PUBLIC
	${PBNI_INCLUDE_DIR}

INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
cmake_minimum_required(VERSION 3.0)

project(lib.cpp.base.pbni-framework)
set(PBNI_FRAMEWORK_VERSION_MAJOR 0 CACHE STRING "Major Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_VERSION_MINOR 1 CACHE STRING "Minor Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_VERSION_BUGFIX 0 CACHE STRING "Bugfix Version of lib.cpp.base.pbni-framework")
set(PBNI_FRAMEWORK_VERSION "${PBNI_FRAMEWORK_VERSION_MAJOR}.${PBNI_FRAMEWORK_VERSION_MINOR}.${PBNI_FRAMEWORK_VERSION_BUGFIX}")

# Check for 32 bit
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Powerbuilder runs on 32 bits, please choose a 32 bit plattform using '-A Win32'")
endif()

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-DWIN32_LEAN_AND_MEAN)
# To be able to use __VA_OPT__
add_compile_options("/Zc:preprocessor")

##################################################
#                     Options                    #
##################################################


set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Location of built dlls/libraries")

set(PBNI_DIR "C:/Program Files (x86)/Appeon/PowerBuilder 17.0/SDK/PBNI" CACHE PATH "PATH of PowerBuilder Native Interface SDK")
set(PBNI_INCLUDE_DIR "${PBNI_DIR}/include" CACHE PATH "PowerBuilder Native Interface header files location")
set(PBNI_LIBRARY "${PBNI_DIR}/lib/pbni.lib" CACHE FILEPATH "PowerBuilder Native Interface library for release target")

set(BOOST_INCLUDE_DIR "C:/Program Files/boost/boost_1_79_0" CACHE FILEPATH "Header files for boost library")


add_subdirectory(src)
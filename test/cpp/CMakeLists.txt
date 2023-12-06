cmake_minimum_required(VERSION 3.5)


##################################################
#                    Options                     #
##################################################

set(OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../../out" CACHE PATH "Location of built dlls/libraries")
set(A3_LIB_PATH "${CMAKE_SOURCE_DIR}/../pb" CACHE PATH "Location of A3, is used to copy the resulting DLL")


##################################################
#              libFrameworkTester                #
##################################################

project(lib.pbni.base.framework-tester LANGUAGES CXX)

add_library(libFrameworkTester SHARED
	src/tester.h
	src/tester.cpp
)

set_target_properties(libFrameworkTester
PROPERTIES 
	OUTPUT_NAME ${CMAKE_PROJECT_NAME}
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

install(TARGETS libFrameworkTester
	RUNTIME DESTINATION ${A3_LIB_PATH}
)


add_subdirectory("../../" "${CMAKE_CURRENT_BINARY_DIR}/lib.pbni.base.framework")
target_link_libraries(libFrameworkTester
PRIVATE
	inf::pbni-framework
)
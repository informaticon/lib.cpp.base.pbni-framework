CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

##################################################
#                 PBNI Framework                 #
##################################################

project(lib.cpp.base.pbni-framework CXX)

include_directories(
	${PBNI_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
)

file(GLOB SOURCE *.cpp *.h)

set(
    source_list
    "Framework.cpp"
    "Framework.h"
    "Errors.h"
    "Strings.h"
    "PBTypes.h"
    "descriptions/MethodDescription.h"
    "descriptions/ClassDescription.h"
	"types/PBArray.h"
	"types/PBBlob.cpp"
	"types/PBBlob.h"
	"types/PBDateTimes.cpp"
	"types/PBDateTimes.h"
	"types/PBNumbers.h"
	"types/PBObjects.h"
	"types/PBString.cpp"
	"types/PBString.h"
)

add_library(libFramework STATIC ${source_list})


foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()


target_link_libraries( libFramework
	${PBNI_LIBRARY}
)

set_target_properties( libFramework PROPERTIES
	LINK_FLAGS "/MACHINE:X86"
	OUTPUT_NAME "lib.cpp.base.pbni-framework"
	RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
	LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

install(TARGETS libFramework
	RUNTIME DESTINATION ${A3_LIB_PATH}
)

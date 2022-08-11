CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


# Check for 32 bit
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Powerbuilder runs on 32 bits, please choose a 32 bit plattform using '-A Win32'")
endif()

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-DWIN32_LEAN_AND_MEAN)

set(CMAKE_CXX_STANDARD 20)
# To be able to use __VA_OPT__
add_compile_options("/Zc:preprocessor")


##################################################
#                 PBNI Framework                 #
##################################################


project(lib.cpp.base.pbni-framework CXX)

target_include_directories( ${PBNI_TARGET} PUBLIC
	${PBNI_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
)

target_link_libraries( ${PBNI_TARGET}
	${PBNI_LIBRARY}
)

target_sources( ${PBNI_TARGET} PUBLIC
    "${SUBFOLDER}/Framework.cpp"
    "${SUBFOLDER}/Framework.h"
    "${SUBFOLDER}/Errors.h"
    "${SUBFOLDER}/dllmain.cpp"

    "${SUBFOLDER}/MethodDescription.h"
    "${SUBFOLDER}/ClassDescription.h"
	
    "${SUBFOLDER}/PBTypes.h"
	"${SUBFOLDER}/PBArray.h"
	"${SUBFOLDER}/PBBlob.cpp"
	"${SUBFOLDER}/PBBlob.h"
	"${SUBFOLDER}/PBDateTimes.cpp"
	"${SUBFOLDER}/PBDateTimes.h"
	"${SUBFOLDER}/PBNumbers.h"
	"${SUBFOLDER}/PBObjects.h"
	"${SUBFOLDER}/PBString.cpp"
	"${SUBFOLDER}/PBString.h"
)

source_group( "Framework" FILES
	"${SUBFOLDER}\\Framework.cpp"
    "${SUBFOLDER}\\Framework.h"
    "${SUBFOLDER}\\Errors.h"
	"${SUBFOLDER}\\dllmain.cpp"
)

source_group( "Framework\\Descriptions" FILES
	"${SUBFOLDER}\\MethodDescription.h"
	"${SUBFOLDER}\\ClassDescription.h"
)

source_group( "Framework\\Types" FILES
    "${SUBFOLDER}\\PBTypes.h"
	"${SUBFOLDER}\\PBArray.h"
	"${SUBFOLDER}\\PBBlob.cpp"
	"${SUBFOLDER}\\PBBlob.h"
	"${SUBFOLDER}\\PBDateTimes.cpp"
	"${SUBFOLDER}\\PBDateTimes.h"
	"${SUBFOLDER}\\PBNumbers.h"
	"${SUBFOLDER}\\PBObjects.h"
	"${SUBFOLDER}\\PBString.cpp"
	"${SUBFOLDER}\\PBString.h"
)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)


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
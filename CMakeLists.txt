CMAKE_MINIMUM_REQUIRED(VERSION 3.18)


##################################################
#                    Options                     #
##################################################

if (MINGW)
	set(PBNI_INCLUDE_DIR "~/.local/include/pbni" CACHE PATH "PowerBuilder Native Interface header files location")
else()
	set(PBNI_INCLUDE_DIR "$C:/Program Files (x86)/Appeon/PowerBuilder 17.0/SDK/PBNI/include" CACHE PATH "PowerBuilder Native Interface header files location")
endif()

option(PBNI_USE_STATIC_RUNTIME  "Whether to set the MTD option when building" OFF)

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
	src/Helper.h
	src/PBValue.h
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
	src/PBAny.cpp
	src/PBAny.h
)

set(headers ${src})
list(APPEND headers ${descriptions})
list(APPEND headers ${types})
list(FILTER headers INCLUDE REGEX "\.h$")

add_library(libPBNIFramework OBJECT
	${src}
	${descriptions}
	${types}
)
source_group("Source Files" FILES ${src})
source_group("Source Files/Descriptions" FILES ${descriptions})
source_group("Source Files/Types" FILES ${types})

if (MINGW)
	target_sources(libStringUtils
	PRIVATE
		mingw-exports.def
	)
endif()


target_precompile_headers(libPBNIFramework PUBLIC ${headers})

target_compile_features(libPBNIFramework PUBLIC cxx_std_20)

if (NOT MINGW)
	# To be able to use __VA_OPT__
	target_compile_options(libPBNIFramework PUBLIC /Zc:preprocessor)

	if(PBNI_USE_STATIC_RUNTIME) 
		cmake_policy(GET CMP0091 CMP0091_Value)
		if(NOT ${CMP0091_Value} STREQUAL "NEW")
			message(FATAL_ERROR "To be able to Statically link the Runtime, you need to set the CMP0091 option to NEW!")
		endif()

		set_target_properties(libPBNIFramework
		PROPERTIES 
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
		)
	endif()
endif()

target_compile_definitions(libPBNIFramework
PUBLIC
	-DUNICODE
	-D_UNICODE
	-DWIN32_LEAN_AND_MEAN
	-DNOMINMAX
)

if (MINGW)
	find_package(Boost
	REQUIRED
		stacktrace_backtrace
	)

	target_link_libraries(libPBNIFramework
	PUBLIC
		Boost::stacktrace_backtrace
	)
else()
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
endif()

target_include_directories(libPBNIFramework
INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/src

PUBLIC
	${PBNI_INCLUDE_DIR}

	# Header only libraries
	Boost::utility
	Boost::multiprecision
)

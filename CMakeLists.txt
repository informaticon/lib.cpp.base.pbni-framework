CMAKE_MINIMUM_REQUIRED(VERSION 3.18)


##################################################
#                    Options                     #
##################################################

option(PBNI_USE_STATIC_RUNTIME  "Whether to set the MTD option when building" OFF)

##################################################
#                 PBNI Framework                 #
##################################################

project(lib.cpp.base.pbni-framework LANGUAGES CXX)

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

add_library(pbni-framework OBJECT
	${src}
	${descriptions}
	${types}
)
add_library(inf::pbni-framework ALIAS pbni-framework)

source_group("Source Files" FILES ${src})
source_group("Source Files/Descriptions" FILES ${descriptions})
source_group("Source Files/Types" FILES ${types})

if (MINGW)
	target_sources(libStringUtils
	PRIVATE
		mingw-exports.def
	)
endif()


message(${headers})
# target_precompile_headers(pbni-framework PUBLIC ${headers})

target_compile_features(pbni-framework PUBLIC cxx_std_20)

if (NOT MINGW)
	# To be able to use __VA_OPT__
	target_compile_options(pbni-framework PUBLIC /Zc:preprocessor)

	if(PBNI_USE_STATIC_RUNTIME) 
		cmake_policy(GET CMP0091 CMP0091_Value)
		if(NOT ${CMP0091_Value} STREQUAL "NEW")
			message(FATAL_ERROR "To be able to Statically link the Runtime, you need to set the CMP0091 option to NEW!")
		endif()

		set_target_properties(pbni-framework
		PROPERTIES 
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
		)
	endif()
endif()

target_compile_definitions(pbni-framework
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

	target_link_libraries(pbni-framework
	PUBLIC
		Boost::stacktrace_backtrace
	)
else()
	find_package(Boost
	REQUIRED
		stacktrace_windbg
	)

	target_link_libraries(pbni-framework
	PUBLIC
		Boost::stacktrace_windbg
	)
endif()

if(NOT INF_VCPKG_INSTALL)
	target_include_directories(pbni-framework
	INTERFACE
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/extern/pbni/include"
	)

else()
	target_include_directories(pbni-framework
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	PRIVATE
		"extern/pbni/include"
	)

	include(GNUInstallDirs)

	install(TARGETS pbni-framework
	EXPORT pbni-framework_targets
		OBJECTS DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	)

	install(DIRECTORY extern/pbni/include/pbni DESTINATION include)
	install(FILES ${headers} DESTINATION include/PBNIFramework)

	install(EXPORT pbni-framework_targets
		FILE pbni-framework-targets.cmake
		NAMESPACE inf::
		DESTINATION share/pbni-framework
	)

	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/pbni-framework-config.cmake"
		"include(CMakeFindDependencyMacro)\n"
		"find_dependency(Boost REQUIRED stacktrace_windbg)\n"
		"include(\"\${CMAKE_CURRENT_LIST_DIR}/pbni-framework-targets.cmake\")\n"
	)

	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pbni-framework-config.cmake"
		DESTINATION share/pbni-framework
	)
endif()

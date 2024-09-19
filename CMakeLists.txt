CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

project(lib.cpp.base.pbni-framework LANGUAGES CXX)

##################################################
#                    Options                     #
##################################################

option(PBNI_USE_STATIC_RUNTIME "Whether to set the MTD option when building" OFF)

include(GNUInstallDirs)
set(INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/pbni-framework" CACHE PATH "Location of installed CMake Files")
set(PBNI_SDK_DIRECTORY "C:/Program Files (x86)/Appeon/PowerBuilder 22.0/SDK/PBNI" CACHE PATH "Location of the required PBNI Sources")

##################################################
#                 PBNI Framework                 #
##################################################

# Check for 32 bit
# if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
#   message(FATAL_ERROR "Powerbuilder runs on 32 bits, choose a 32 bit plattform using '-A Win32'")
# endif()

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

set(pbni-helpers
    ${PBNI_SDK_DIRECTORY}/src/pbarray.cpp
    ${PBNI_SDK_DIRECTORY}/src/pbfuninv.cpp
    ${PBNI_SDK_DIRECTORY}/src/pbobject.cpp
)

set(headers ${src})
list(APPEND headers ${descriptions})
list(APPEND headers ${types})
list(FILTER headers INCLUDE REGEX "\.h$")

add_library(pbni-framework OBJECT
    ${src}
    ${descriptions}
    ${types}
    ${pbni-helpers}
)
add_library(inf::pbni-framework ALIAS pbni-framework)

source_group("Source Files" FILES ${src})
source_group("Source Files/Descriptions" FILES ${descriptions})
source_group("Source Files/Types" FILES ${types})

if(MINGW)
    target_sources(pbni-framework
    PRIVATE
        mingw-exports.def
    )
endif()


target_compile_features(pbni-framework PUBLIC cxx_std_20)

if(MSVC)
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

if(MINGW)
    set(STACKTRACE_LIBRARY "stacktrace_backtrace")
else()
    set(STACKTRACE_LIBRARY "stacktrace_windbg")
endif()

find_package(Boost
REQUIRED
    ${STACKTRACE_LIBRARY}
)
target_link_libraries(pbni-framework
PUBLIC
    Boost::${STACKTRACE_LIBRARY}
)

target_include_directories(pbni-framework
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PBNI_SDK_DIRECTORY}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


install(FILES ${headers} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/PBNIFramework")


install(TARGETS pbni-framework
    EXPORT pbni-framework-exports
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

install(EXPORT pbni-framework-exports
    FILE pbni-framework-targets.cmake
    NAMESPACE inf::
    DESTINATION "${INSTALL_CMAKEDIR}"
)

set(PBNI_FRAMEWORK_HEADERS ${headers})
list(TRANSFORM PBNI_FRAMEWORK_HEADERS REPLACE "^src/(.+)$" "<PBNIFramework/\\1>")

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "cmake/pbni-framework-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/pbni-framework-config.cmake"
    INSTALL_DESTINATION "${INSTALL_CMAKEDIR}"
    NO_SET_AND_CHECK_MACRO
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pbni-framework-config.cmake" DESTINATION "${INSTALL_CMAKEDIR}")

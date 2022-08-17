CMAKE_MINIMUM_REQUIRED(VERSION 3.18)


##################################################
#                     Extern                     #
##################################################

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(BOOST_STACKTRACE_ENABLE_NOOP OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_noop")
set(BOOST_STACKTRACE_ENABLE_BACKTRACE OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_backtrace")
set(BOOST_STACKTRACE_ENABLE_ADDR2LINE OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_addr2line")
set(BOOST_STACKTRACE_ENABLE_BASIC OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_basic")
set(BOOST_STACKTRACE_ENABLE_WINDBG ON CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_windbg")
set(BOOST_STACKTRACE_ENABLE_WINDBG_CACHED OFF CACHE BOOL "Boost.Stacktrace: build boost_stacktrace_windbg_cached")


# Dependencies
add_subdirectory(boost_config)
add_subdirectory(boost_core)
add_subdirectory(boost_io)
add_subdirectory(boost_preprocessor)
add_subdirectory(boost_assert)
add_subdirectory(boost_static_assert)
add_subdirectory(boost_throw_exception)
add_subdirectory(boost_array)
add_subdirectory(boost_container_hash)
add_subdirectory(boost_predef)
add_subdirectory(boost_winapi)

add_subdirectory(boost_type_traits)
add_subdirectory(boost_utility)
add_subdirectory(boost_multiprecision)
add_subdirectory(boost_stacktrace)

cmake_minimum_required(VERSION 3.13)

### Extract UCL version
# Read version file
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/UCL/version.hpp" VERSION_FILE_CONTENT)

# Extract version
string(REGEX MATCH "UCL_VERSION_MAJOR = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_MAJOR ${CMAKE_MATCH_1})

string(REGEX MATCH "UCL_VERSION_MINOR = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_MINOR ${CMAKE_MATCH_1})

string(REGEX MATCH "UCL_VERSION_PATCH = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_PATCH ${CMAKE_MATCH_1})

# Concatenation
set(UCL_VERSION "${UCL_VERSION_MAJOR}.${UCL_VERSION_MINOR}.${UCL_VERSION_PATCH}")
message(STATUS "UCL version: ${UCL_VERSION}")



project(
    ucl
    VERSION ${UCL_VERSION}
    DESCRIPTION "Universal configuration loader for C++ programs"
    LANGUAGES CXX
)



### Link type
if(NOT DEFINED UCL_LINK_TYPE)
    set(UCL_LINK_TYPE SHARED)
elseif(UCL_LINK_TYPE NOT MATCHES "SHARED|STATIC")
    message(FATAL_ERROR "invalid UCL_LINK_TYPE! Available: SHARED or STATIC")
endif
message(STATUS "Using ${UCL_LINK_TYPE} UCL")



### Target
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/ucl)
set(PUBLIC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PRIVATE_INCLUDES ${SOURCES_DIR})
file(GLOB_RECURSE PUBLIC_HEADERS "${PUBLIC_INCLUDES}/*.hpp")
file(GLOB_RECURSE PRIVATE_HEADERS "${PRIVATE_INCLUDES}/*.hpp")
file(GLOB_RECURSE SOURCES "${SOURCES_DIR}/*.cpp")

add_library(
    ucl
    ${UCL_LINK_TYPE}
    ${SOURCES}
    ${PUBLIC_HEADERS} ${PRIVATE_HEADERS}
)
target_include_directories(
    ucl
    PUBLIC ${PUBLIC_INCLUDES}
    PRIVATE ${PRIVATE_INCLUDES}
)
target_compile_definitions(
    ucl
    PUBLIC
        $<$<STREQUAL:${UCL_LINK_TYPE},SHARED>:UCL_SHARED>
        $<$<STREQUAL:${UCL_LINK_TYPE},STATIC>:UCL_STATIC>
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:Release>:NDEBUG>
        $<$<STREQUAL:${UCL_LINK_TYPE},SHARED>:UCL_EXPORTS>
)
target_compile_options(
    ucl
    PUBLIC
    PRIVATE
        $<$<CONFIG:Debug>:-g3 -Og> $<$<CONFIG:Release>:-g0 -O3>
        -Wall -Wextra -Wpedantic $<$<CONFIG:Release>:-Werror -Wno-error=deprecated-declarations>
        -std=c++11 -pipe
        $<$<STREQUAL:${UCL_LINK_TYPE},SHARED>:-fvisibility=hidden>
)
target_link_options(ucl PUBLIC PRIVATE)
target_link_directories(ucl PUBLIC PRIVATE)
target_link_libraries(ucl PUBLIC PRIVATE)
set_target_properties(ucl
    PROPERTIES
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
        DEFINE_SYMBOL ""
        VERSION       "${UCL_VERSION}"
        SOVERSION     "${UCL_VERSION_MAJOR}"
)

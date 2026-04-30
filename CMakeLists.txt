cmake_minimum_required(VERSION 3.15)

### Extract UCL version
# Read version file
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/ucl/version.hpp" VERSION_FILE_CONTENT)

# Extract version
string(REGEX MATCH "UCL_VERSION_MAJOR = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_MAJOR ${CMAKE_MATCH_1})

string(REGEX MATCH "UCL_VERSION_MINOR = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_MINOR ${CMAKE_MATCH_1})

string(REGEX MATCH "UCL_VERSION_PATCH = ([0-9]+)" _ ${VERSION_FILE_CONTENT})
set(UCL_VERSION_PATCH ${CMAKE_MATCH_1})

# Concatenation
set(UCL_VERSION "${UCL_VERSION_MAJOR}.${UCL_VERSION_MINOR}.${UCL_VERSION_PATCH}")
message(STATUS "UCL version: v${UCL_VERSION}")



### Define project
project(
    ucl
    VERSION ${UCL_VERSION}
    DESCRIPTION "Universal configuration loader for C++ programs"
    LANGUAGES CXX
)



### C++ flags
# MSVC not supported yet
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_GENERATOR MATCHES "Visual Studio")
    message(FATAL_ERROR "MSVC compiler and MS Visual Studio generators are not supported yet")
endif()

# Standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link type
if(UCL_LINK_TYPE STREQUAL "SHARED")
    set(BUILD_SHARED_LIBS ON)
elseif(UCL_LINK_TYPE STREQUAL "STATIC")
    set(BUILD_SHARED_LIBS OFF)
endif()



### Target
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/ucl)
set(PUBLIC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PRIVATE_INCLUDES ${SOURCES_DIR})
file(GLOB_RECURSE PUBLIC_HEADERS "${PUBLIC_INCLUDES}/*.hpp")
file(GLOB_RECURSE PRIVATE_HEADERS "${PRIVATE_INCLUDES}/*.hpp")
file(GLOB_RECURSE SOURCES "${SOURCES_DIR}/*.cpp")

add_library(
    ucl
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
        $<$<BOOL:${BUILD_SHARED_LIBS}>:UCL_SHARED>
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:UCL_STATIC>
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
)
target_compile_options(
    ucl
    PUBLIC
    PRIVATE
        -Wall -Wextra -Wpedantic $<$<NOT:$<CONFIG:Debug>>:-Werror -Wno-error=deprecated-declarations>
        -pipe
        $<$<BOOL:${BUILD_SHARED_LIBS}>:-fvisibility=hidden>
)
target_link_options(ucl PUBLIC PRIVATE)
target_link_directories(ucl PUBLIC PRIVATE)
target_link_libraries(ucl PUBLIC PRIVATE)
set_target_properties(ucl
    PROPERTIES
        PUBLIC_HEADER "${PUBLIC_HEADERS}"
        DEFINE_SYMBOL "UCL_EXPORTS"
        VERSION       "${UCL_VERSION}"
        SOVERSION     "${UCL_VERSION_MAJOR}"
        POSITION_INDEPENDENT_CODE ON
)

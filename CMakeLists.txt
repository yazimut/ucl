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
# Standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link type
if(UCL_LINK_TYPE STREQUAL "SHARED")
    set(BUILD_SHARED_LIBS ON)
elseif(UCL_LINK_TYPE STREQUAL "STATIC")
    set(BUILD_SHARED_LIBS OFF)
endif()

# Native CPU optimization
option(UCL_NATIVE_CPU_OPTIMIZATION OFF)



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
        $<$<BOOL:${UCL_NATIVE_CPU_OPTIMIZATION}>:-march=native -mtune=native>
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



### Docs
option(UCL_BUILD_DOCS "Build UCL documentation" ON)
if(UCL_BUILD_DOCS)
    find_package(Doxygen 1.9.0 REQUIRED)
    add_custom_target(
        ucl_docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "UCL: generating documentation"
        VERBATIM
    )
endif()



### Tests
option(UCL_RUN_TESTS "Build and run UCL tests" OFF)
if(UCL_RUN_TESTS)
    # Build tests
    add_executable(
        ucl_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tests/main.cpp
        ${PUBLIC_HEADERS}
    )
    target_compile_definitions(
        ucl_tests
        PRIVATE
            $<$<CONFIG:Debug>:DEBUG>
            $<$<NOT:$<CONFIG:Debug>>:NDEBUG>
    )
    target_compile_options(
        ucl_tests
        PRIVATE
            -Wall -Wextra -Wpedantic $<$<NOT:$<CONFIG:Debug>>:-Werror -Wno-error=deprecated-declarations>
            -pipe -s
            -march=native -mtune=native
    )
    target_link_options(ucl_tests PUBLIC PRIVATE)
    target_link_directories(ucl_tests PUBLIC PRIVATE)
    target_link_libraries(ucl_tests PUBLIC ucl)

    # Run tests
    add_custom_target(
        ucl_tests_run ALL
        COMMAND ${CMAKE_BINARY_DIR}/ucl_tests --all
        DEPENDS ucl_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif()

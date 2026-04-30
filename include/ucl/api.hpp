/**
 * @file api.hpp
 * @brief Declaration of library API export/import
 * @details Each header of UCL includes this file. \n
 * Contains:
 *   * C++ standard checking
 *   * Definitions of API macros
 *   * First and global definition of UCL namespace
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 * @copyright Copyright (c) Eugene Azimut, 2026 \n
 * MIT License: this software may be freely used, modified,
 * and distributed, provided that this notice is retained.
 */
#pragma once

#if !defined(__cplusplus)
    #error "Required language is C++"
#endif

#if __cplusplus < 201703L
    #error "Required C++ standard is C++17 and higher"
#endif

/** @cond IGNORE */
#if defined(_WIN32)
    // Microsoft Windows
    #if defined(UCL_STATIC)
        #define UCL_API
    #else
        #if !defined(UCL_SHARED)
            #define UCL_SHARED
        #endif

        #if defined(UCL_EXPORTS)
            #define UCL_API __declspec(dllexport)
        #else
            #define UCL_API __declspec(dllimport)
        #endif
    #endif

    #define UCL_HIDDEN
#else
    // Linux,
    // MacOS (OS X),
    // Android,
    // iOS,
    // Unix-like
    #if defined(UCL_STATIC)
        #define UCL_API
        #define UCL_HIDDEN
    #else
        #if !defined(UCL_SHARED)
            #define UCL_SHARED
        #endif

        #if defined(UCL_EXPORTS)
            #define UCL_API __attribute__((visibility("default")))
            #define UCL_HIDDEN __attribute__((visibility("hidden")))
        #else
            #define UCL_API
            #define UCL_HIDDEN
        #endif
    #endif
#endif
/** @endcond */



/**
 * @brief Marks symbol as deprecated
 * @version 1.0.0
 * @authors Eugene Azimut
 */
#define UCL_DEPRECATED(msg) [[deprecated(msg)]]



/**
 * @namespace ucl
 * @brief UCL namespace
 * @details Contains all library definitions
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 */
namespace ucl {}

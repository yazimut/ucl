/**
 * @file version.hpp
 * @brief Declaration of library current version
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 * @copyright Copyright (c) Eugene Azimut, 2026 \n
 * MIT License: this software may be freely used, modified,
 * and distributed, provided that this notice is retained.
 */
#pragma once
#include "api.hpp"

#include <cstddef>
#include <cstdint>



namespace ucl {
    /**
     * @namespace ucl::version
     * @brief Contains library version definitions
     *
     * @version 1.0.0
     * @authors Eugene Azimut
     */
    namespace version {
        /**
         * @brief Library major update
         * @details Can be [0;255]
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        constexpr uint32_t UCL_VERSION_MAJOR = 1 & 0xFF;

        /**
         * @brief Library minor update
         * @details Can be [0;255]
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        constexpr uint32_t UCL_VERSION_MINOR = 0 & 0xFF;

        /**
         * @brief Library patch update
         * @details Can be [0;65535]
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        constexpr uint32_t UCL_VERSION_PATCH = 0 & 0xFFFF;

        /**
         * @brief Numeric library version number
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        constexpr uint32_t UCL_VERSION = (
            (UCL_VERSION_MAJOR << 24) |
            (UCL_VERSION_MINOR << 16) |
            (UCL_VERSION_PATCH)
        );

        /**
         * @brief Maximum size of library version string
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        constexpr size_t MAX_UCL_VERSION_STRING_SIZE = 14;

        /**
         * @brief Get library version number
         * @return Version number
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        UCL_API uint32_t getVersionNumeric() noexcept;

        /**
         * @brief Get library version string in format X.X.X
         * @return Version string
         *
         * @throw std::bad_alloc in case of memory allocation failure
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        UCL_API const char *getVersionString();
    }
}

/**
 * @file IConfig.hpp
 * @brief Declaration of configuration interface
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 * @copyright Copyright (c) Eugene Azimut, 2026 \n
 * MIT License: this software may be freely used, modified,
 * and distributed, provided that this notice is retained.
 */
#pragma once
#include "api.hpp"



namespace ucl {
    /**
     * @class IConfig
     * @brief Configuration interface
     * @details Contains methods for loading/saving application configuration
     *
     * @warning This is an abstract class. Don't create its instances directly!
     *
     * @version 1.0.0
     * @authors Eugene Azimut
     */
    class UCL_API IConfig {
    public:
    //* Ctors and dtor
        /**
         * @brief Default constructor
         * @details Creates new instance
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        IConfig();

        /**
         * @brief Destroies instance
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        virtual ~IConfig() noexcept = 0;
    };
}

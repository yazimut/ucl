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

#include <string>



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
        IConfig(const std::string &CfgName);

        /**
         * @brief Copy constructor
         * @details Creates new instance as a copy of Other
         *
         * @param[in] Other Instance to copy
         *
         * @throw std::bad_alloc in case of memory allocation failure
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        IConfig(const IConfig &Other);

        /**
         * @brief Move constructor
         * @details Creates new instance moving Other
         *
         * @param[in] Other Instance to move
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        IConfig(IConfig &&Other) noexcept;

        /**
         * @brief Destroies instance
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        virtual ~IConfig() noexcept = 0;

    //* Operators
        /**
         * @brief Copy assignment operator
         * @details Copies Right instance to current one
         *
         * @param[in] Right Instance to copy
         * @returns Reference to current instance
         *
         * @throw std::bad_alloc in case of memory allocation failure
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        IConfig &operator = (const IConfig &Right);

        /**
         * @brief Move assignment operator
         * @details Moves Right instance to current one
         *
         * @param[in] Right Instance to move
         * @returns Reference to current instance
         *
         * @version 1.0.0
         * @authors Eugene Azimut
         */
        IConfig &operator = (IConfig &&Right) noexcept;

    private:
    //* Variables
        std::string mCfgName;        ///< Config file name
    };
}

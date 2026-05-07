/**
 * @file IConfig.cpp
 * @brief Definition of configuration interface
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 * @copyright Copyright (c) Eugene Azimut, 2026 \n
 * MIT License: this software may be freely used, modified,
 * and distributed, provided that this notice is retained.
 */
#include <ucl/IConfig.hpp>

using namespace std;
using namespace ucl;



IConfig::IConfig() {}

IConfig::IConfig(const IConfig &Other) {}

IConfig::IConfig(IConfig &&Other) {}

IConfig::~IConfig() noexcept {}

IConfig &IConfig::operator = (const IConfig &Right) {
    if (this == &Right) return *this;
    return *this;
}

IConfig &IConfig::operator = (IConfig &&Right) {
    if (this == &Right) return *this;
    return *this;
}

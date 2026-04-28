/**
 * @file version.cpp
 * @brief Definition of library current version
 *
 * @version 1.0.0
 * @authors Eugene Azimut
 * @copyright Copyright (c) Eugene Azimut, 2026 \n
 * MIT License: this software may be freely used, modified,
 * and distributed, provided that this notice is retained.
 */
#include <ucl/version.hpp>
#include <string>

using namespace std;
using namespace ucl;
using namespace ucl::version;



uint32_t version::getVersionNumeric() noexcept {
    return UCL_VERSION;
}

const char *version::getVersionString() {
    static string Version = "";
    if (Version.size() == 0) {
        Version.reserve(MAX_UCL_VERSION_STRING_SIZE);
        Version += to_string(UCL_VERSION_MAJOR) + '.';
        Version += to_string(UCL_VERSION_MINOR) + '.';
        Version += to_string(UCL_VERSION_PATCH);
    }
    return Version.c_str();
}

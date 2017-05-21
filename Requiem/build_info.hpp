#pragma once

#include "Debug_Utils.hpp"

#define BUILD_VERSION_MAJOR std::string("0")
#define BUILD_VERSION_MINOR std::string("7")

#ifdef DEBUG
#define BUILD_EDITION std::string("(developers release)\n")
#else
#define BUILD_EDITION std::string("(testing release)\n")
#endif

#pragma once

#include <cstdio>

#define JSON_CPP_SERIALIZE_FLOAT(outBuffer, x) snprintf(outBuffer, sizeof(outBuffer), "%.9g", x)
#define JSON_CPP_SERIALIZE_DOUBLE(outBuffer, x) snprintf(outBuffer, sizeof(outBuffer), "%.17g", x)

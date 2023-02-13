
#pragma once

#include <string>
#include <set>
#include "octopus.h"

namespace octopus {

bool validate(const Octopus &document, std::set<std::string> &layerIdSet, std::string *errorMessagePtr = nullptr, const void **datapointPtr = nullptr);

}

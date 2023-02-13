
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"

namespace octopus {

struct Page {
    std::string id;
    std::string name;
    std::vector<Reference> children;
    nonstd::optional<std::string> description;
    nonstd::optional<std::string> hash;
};

}


#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "resource.h"
#include "asset.h"

namespace octopus {

struct Library {
    std::string id;
    std::string name;
    std::vector<Reference> children;
    nonstd::optional<ResourceLocation> location;
    nonstd::optional<ResourceLocation> preview;
    nonstd::optional<Assets> assets;
    nonstd::optional<std::string> description;
    nonstd::optional<std::string> hash;
};

}

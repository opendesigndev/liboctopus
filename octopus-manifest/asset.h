
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "resource.h"

namespace octopus {

struct AssetFont {
    nonstd::optional<ResourceLocation> location;
    nonstd::optional<std::string> fontType;
    std::string refId;
    std::string name;
};

struct AssetImage {
    ResourceLocation location;
    std::string refId;
    std::string name;
};

struct Assets {
    std::vector<AssetFont> fonts;
    std::vector<AssetImage> images;
};

}

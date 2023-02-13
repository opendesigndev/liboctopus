
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "status.h"
#include "resource.h"
#include "asset.h"
#include "artifact.h"

namespace octopus {

struct Chunk {
    enum class Type {
        STYLE_LAYER,
        STYLE_FILL,
        STYLE_TEXT,
        STYLE_EFFECT,
        STYLE_GRID
    };
    std::string id;
    std::string name;
    Type type;
    ResourceLocation location;
    std::vector<Artifact> artifacts;
    nonstd::optional<ResourceLocation> preview;
    nonstd::optional<Assets> assets;
    nonstd::optional<std::string> description;
    nonstd::optional<std::string> hash;
    nonstd::optional<Status> status;
};

}

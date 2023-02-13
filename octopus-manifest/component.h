
#pragma once

#include <string>
#include <vector>
#include <map>
#include <nonstd/optional.hpp>
#include "general.h"
#include "status.h"
#include "resource.h"
#include "asset.h"
#include "artifact.h"

namespace octopus {

struct ComponentSet {
    std::string id;
    std::string name;
    nonstd::optional<std::string> description;
};

struct Component {
    enum class Role {
        COMPONENT,
        ARTBOARD,
        PASTEBOARD,
        PARTIAL
    };
    struct VariantMeta {
        ComponentSet of;
        std::map<std::string, std::string> properties;
        nonstd::optional<std::string> description;
    };
    std::string id;
    std::string name;
    Role role = Role::COMPONENT;
    Bounds bounds;
    std::vector<Reference> dependencies;
    ResourceLocation location;
    std::vector<Artifact> artifacts;
    nonstd::optional<Reference> parentId;
    nonstd::optional<ResourceLocation> preview;
    nonstd::optional<Assets> assets;
    nonstd::optional<VariantMeta> variant;
    nonstd::optional<std::string> description;
    nonstd::optional<std::string> hash;
    nonstd::optional<Status> status;
};

}

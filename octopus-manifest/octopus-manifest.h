
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "resource.h"
#include "library.h"
#include "chunk.h"
#include "component.h"
#include "page.h"

#define OCTOPUS_MANIFEST_VERSION "3.0.2"

namespace octopus {

struct OctopusManifest {
    struct Origin {
        std::string name;
        std::string version;
    };
    std::string version;
    Origin origin;
    std::string name;
    std::vector<Page> pages;
    std::vector<Component> components;
    std::vector<Library> libraries;
    std::vector<Chunk> chunks;
    std::string resourcesBase;
    nonstd::optional<ResourceLocation> interactions;
    nonstd::optional<std::string> hash;
};

}

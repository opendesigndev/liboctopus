
#pragma once

#include "resource.h"

namespace octopus {

struct Artifact {
    enum class Type {
        OCTOPUS,
        OCTOPUS_EXPANDED,
        SOURCE
    };
    Type type;
    ResourceLocation location;
};

}

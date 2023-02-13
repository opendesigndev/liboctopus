
#pragma once

#include <string>
#include <list>
#include <nonstd/optional.hpp>
#include <nonstd/optional_ptr.hpp>
#include "general.h"
#include "filter.h"
#include "fill.h"
#include "stroke.h"
#include "effect.h"
#include "shape.h"
#include "text.h"
#include "layer.h"

#define OCTOPUS_VERSION "3.0.1"

namespace octopus {

struct Octopus {
    enum class Type {
        OCTOPUS_COMPONENT
    };
    Type type = Type::OCTOPUS_COMPONENT;
    std::string version;
    std::string id;
    nonstd::optional<Dimensions> dimensions;
    nonstd::optional_ptr<Layer> content;
};

}

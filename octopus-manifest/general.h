
#pragma once

#include <string>

namespace octopus {

/// Manifest bounds only
struct Bounds {
    double x, y;
    double width, height;
};

struct Reference {
    enum class Type {
        CHUNK,
        COMPONENT,
        ARTBOARD
    };
    Type type;
    std::string id;
};

}

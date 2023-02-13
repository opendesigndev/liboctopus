
#pragma once

#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "filter.h"

namespace octopus {

struct Gradient {
    enum class Type {
        LINEAR,
        RADIAL,
        ANGULAR,
        DIAMOND
    };
    enum class Interpolation {
        LINEAR,
        POWER,
        REVERSE_POWER
    };
    struct ColorStop {
        double position;
        Interpolation interpolation = Interpolation::LINEAR;
        nonstd::optional<double> interpolationParameter;
        Color color;
    };
    Type type;
    std::vector<ColorStop> stops;
};

struct Fill {
    enum class Type {
        COLOR,
        GRADIENT,
        IMAGE
    };
    struct Positioning {
        enum class Layout {
            STRETCH,
            FILL,
            FIT,
            TILE
        };
        enum class Origin {
            LAYER,
            PARENT,
            COMPONENT,
            ARTBOARD
        };
        Layout layout = Layout::STRETCH;
        Origin origin = Origin::LAYER;
        double transform[6] = { 1, 0, 0, 1, 0, 0 }; // TODO Transform transform;
    };
    Type type;
    bool visible = true;
    BlendMode blendMode = BlendMode::NORMAL;
    nonstd::optional<Color> color;
    nonstd::optional<Gradient> gradient;
    nonstd::optional<Image> image;
    nonstd::optional<Positioning> positioning;
    nonstd::optional<std::vector<Filter> > filters;
};

}

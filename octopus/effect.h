
#pragma once

#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "filter.h"
#include "fill.h"
#include "stroke.h"

namespace octopus {

struct Shadow {
    Vec2 offset = Vec2();
    double blur = 0;
    double choke = 0;
    Color color;
};

struct Effect {
    enum class Type {
        OVERLAY,
        STROKE,
        DROP_SHADOW,
        INNER_SHADOW,
        GAUSSIAN_BLUR,
        BOUNDED_BLUR,
        BLUR,
        OTHER
    };
    Type type;
    EffectBasis basis = EffectBasis::FILL;
    bool visible = true;
    BlendMode blendMode = BlendMode::NORMAL;
    nonstd::optional<Fill> overlay;
    nonstd::optional<Stroke> stroke;
    nonstd::optional<Shadow> shadow;
    nonstd::optional<double> blur;
    nonstd::optional<std::vector<Filter> > filters; // for blurs only
};

}

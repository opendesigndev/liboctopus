
#pragma once

#include <vector>
#include <nonstd/optional.hpp>
#include "fill.h"

namespace octopus {

struct Stroke {
    enum class Position {
        OUTSIDE,
        CENTER,
        INSIDE
    };
    Fill fill;
    double thickness;
    Position position;
};

struct VectorStroke : Stroke {
    enum class Style {
        SOLID,
        DASHED,
        DOTTED
    };
    enum class LineJoin {
        MITER,
        ROUND,
        BEVEL
    };
    enum class LineCap {
        BUTT,
        ROUND,
        SQUARE
    };
    bool visible = true;
    nonstd::optional<Style> style;
    nonstd::optional<LineJoin> lineJoin;
    nonstd::optional<LineCap> lineCap;
    nonstd::optional<double> miterLimit;
    nonstd::optional<std::vector<double> > dashing;
    nonstd::optional<double> dashOffset;
};

}

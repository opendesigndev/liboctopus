
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "fill.h"
#include "stroke.h"

namespace octopus {

struct Path {
    enum class Type {
        PATH,
        RECTANGLE,
        COMPOUND
    };
    enum class Op {
        UNION,
        INTERSECT,
        SUBTRACT,
        EXCLUDE
    };
    Type type = Type::PATH;
    bool visible = true;
    nonstd::optional<Op> op;
    nonstd::optional<std::string> geometry;
    nonstd::optional<std::vector<Path> > paths;
    nonstd::optional<Rectangle> rectangle;
    nonstd::optional<double> cornerRadius;
    nonstd::optional<std::vector<double> > cornerRadii;
    double transform[6] = { 1, 0, 0, 1, 0, 0 };
};

struct Shape {
    enum class FillRule {
        EVEN_ODD,
        NON_ZERO
    };
    struct Stroke : VectorStroke {
        nonstd::optional<FillRule> fillRule;
        nonstd::optional<Path> path;
    };
    nonstd::optional<FillRule> fillRule;
    nonstd::optional<Path> path;
    std::vector<Fill> fills;
    std::vector<Stroke> strokes;
};

}


#pragma once

#include <array>
#include <string>
#include <nonstd/optional.hpp>
#include "general.h"
#include "filter.h"
#include "fill.h"
#include "stroke.h"
#include "effect.h"
#include "shape.h"
#include "text.h"
#include "override.h"

namespace octopus {

struct LayerChange {
    enum class Subject {
        LAYER,
        SHAPE,
        TEXT,
        FILL,
        STROKE,
        STROKE_FILL,
        EFFECT,
        EFFECT_FILL,
        FILL_FILTER,
        STROKE_FILL_FILTER,
        EFFECT_FILL_FILTER
    };
    enum class Op {
        PROPERTY_CHANGE,
        INSERT,
        REPLACE,
        REMOVE
    };

    struct Values {
        nonstd::optional<Fill> fill;
        nonstd::optional<Shape::Stroke> stroke;
        nonstd::optional<Effect> effect;
        nonstd::optional<Filter> filter;
        nonstd::optional<Shape> shape;
        nonstd::optional<Text> text;

        nonstd::optional<bool> visible;
        nonstd::optional<double> opacity;
        nonstd::optional<BlendMode> blendMode;
        nonstd::optional<std::array<double, 6> > transform;
        nonstd::optional<double> featureScale;
        nonstd::optional<MaskBasis> maskBasis;
        nonstd::optional<std::array<double, 5> > maskChannels;
        nonstd::optional<std::string> name;
        nonstd::optional<std::string> componentId;
        nonstd::optional<std::vector<Effect> > effects;
        nonstd::optional<EffectBasis> basis;
        nonstd::optional<std::vector<Filter> > filters;

        nonstd::optional<std::vector<Fill> > fills;
        nonstd::optional<std::vector<Shape::Stroke> > strokes;
        nonstd::optional<Shape::FillRule> fillRule;
        nonstd::optional<Path> path;

        nonstd::optional<std::string> value;
        nonstd::optional<TextStyle> defaultStyle;
        nonstd::optional<std::vector<StyleRange> > styles;
    };

    Subject subject;
    Op op;
    nonstd::optional<int> index;
    nonstd::optional<int> filterIndex;
    Values values;
};

}

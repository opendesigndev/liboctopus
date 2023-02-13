
#pragma once

#include <string>
#include <nonstd/optional.hpp>

namespace octopus {

enum class BlendMode {
    NORMAL,
    PASS_THROUGH,
    COLOR,
    COLOR_BURN,
    COLOR_DODGE,
    DARKEN,
    DARKER_COLOR,
    DIFFERENCE,
    DIVIDE,
    EXCLUSION,
    HARD_LIGHT,
    HARD_MIX,
    HUE,
    LIGHTEN,
    LIGHTER_COLOR,
    LINEAR_BURN,
    LINEAR_DODGE,
    LINEAR_LIGHT,
    LUMINOSITY,
    MULTIPLY,
    OVERLAY,
    PIN_LIGHT,
    SATURATION,
    SCREEN,
    SOFT_LIGHT,
    SUBTRACT,
    VIVID_LIGHT,
};

enum class MaskBasis {
    SOLID = 0,
    BODY = 1,
    BODY_EMBED = 2,
    FILL = 4,
    FILL_EMBED = 5,
    LAYER_AND_EFFECTS = 7
};

enum class EffectBasis {
    BODY = 1,
    BODY_AND_STROKES = 3,
    FILL = 4,
    LAYER_AND_EFFECTS = 7,
    BACKGROUND = 8
};

struct Color {
    double r;
    double g;
    double b;
    double a = 1;
};

struct Vec2 {
    double x;
    double y;
};

struct Dimensions {
    double width;
    double height;
};

struct Rectangle {
    double x0, y0, x1, y1;
};

struct ImageRef {
    enum class Type {
        PATH,
        RESOURCE_REF
    };
    Type type;
    std::string value;
};

struct Image {
    ImageRef ref;
    nonstd::optional<Rectangle> subsection;
};

}

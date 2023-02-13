
#pragma once

#include <nonstd/optional.hpp>

namespace octopus {

struct ColorAdjustment {
    double hue = 0;
    double saturation = 0;
    double brightness = 0;
    double contrast = 0;
    double exposure = 0;
    double temperature = 0;
    double tint = 0;
    double highlights = 0;
    double shadows = 0;
};

struct Filter {
    enum class Type {
        OPACITY_MULTIPLIER,
        XD_BRIGHTNESS_ADJUSTMENT,
        SKETCH_BRIGHTNESS_ADJUSTMENT,
        SKETCH_COLOR_ADJUSTMENT,
        FIGMA_COLOR_ADJUSTMENT
    };
    Type type;
    bool visible = true;
    nonstd::optional<double> opacity;
    nonstd::optional<double> brightness;
    nonstd::optional<ColorAdjustment> colorAdjustment;
};

}

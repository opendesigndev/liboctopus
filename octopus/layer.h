
#pragma once

#include <array>
#include <string>
#include <vector>
#include <list>
#include <nonstd/optional.hpp>
#include <nonstd/optional_ptr.hpp>
#include "general.h"
#include "effect.h"
#include "shape.h"
#include "text.h"
#include "override.h"

namespace octopus {

struct Layer {
    enum class Type {
        SHAPE,
        TEXT,
        GROUP,
        MASK_GROUP,
        COMPONENT_REFERENCE,
        COMPONENT_INSTANCE
    };
    std::string id; // TODO ID id;
    Type type;
    std::string name;
    bool visible = true;
    double opacity = 1; // TODO Opacity opacity; ?
    BlendMode blendMode = BlendMode::NORMAL;
    double transform[6] = { 1, 0, 0, 1, 0, 0 }; // TODO Transform transform;
    nonstd::optional<double> featureScale;
    nonstd::optional<Shape> shape;
    nonstd::optional<Text> text;
    nonstd::optional_ptr<Layer> mask;
    nonstd::optional<MaskBasis> maskBasis;
    nonstd::optional<std::array<double, 5> > maskChannels;
    nonstd::optional<std::list<Layer> > layers;
    nonstd::optional<std::string> componentId;
    nonstd::optional<std::vector<Override> > overrides;
    std::vector<Effect> effects;
};

}

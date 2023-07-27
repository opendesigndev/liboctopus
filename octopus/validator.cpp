
#include "validator.h"

namespace octopus {

static bool validationError(const void *datapoint, const std::string &errorMessage, std::string *errorMessagePtr, const void **datapointPtr) {
    if (errorMessagePtr)
        *errorMessagePtr = errorMessage;
    if (datapointPtr)
        *datapointPtr = datapoint;
    return false;
}

static bool isBlur(Effect::Type effectType) {
    return effectType == Effect::Type::GAUSSIAN_BLUR || effectType == Effect::Type::BOUNDED_BLUR || effectType == Effect::Type::BLUR;
}

bool validateLayerId(const std::string &layerId) {
    for (char c : layerId) {
        switch (c) {
            case '!': case '$': case '&': case '+': case ',': case '-': case '.': case ';': case '=': case '@': case '^': case '_': case '{': case '}':
                break;
            default:
                if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))
                    return false;
        }
    }
    return true;
}

bool validateColor(const Color &color) {
    return color.r >= 0 && color.r <= 1 && color.g >= 0 && color.g <= 1 && color.b >= 0 && color.b <= 1 && color.a >= 0 && color.a <= 1;
}

bool validateFilter(const Layer &layer, const Filter &filter, std::string *errorMessagePtr, const void **datapointPtr) {
    switch (filter.type) {
        case Filter::Type::OPACITY_MULTIPLIER:
            if (!filter.opacity.has_value())
                return validationError(&filter.opacity, "OPACITY_MULTIPLIER filter within layer "+layer.id+" has no opacity value", errorMessagePtr, datapointPtr);
            if (!(filter.opacity.value() >= 0 && filter.opacity.value() <= 1))
                return validationError(&filter.opacity, "OPACITY_MULTIPLIER filter within layer "+layer.id+" has invalid opacity value", errorMessagePtr, datapointPtr);
            break;
        case Filter::Type::XD_BRIGHTNESS_ADJUSTMENT:
        case Filter::Type::SKETCH_BRIGHTNESS_ADJUSTMENT:
            if (!filter.brightness.has_value())
                return validationError(&filter.brightness, "Brightness adjustment filter within layer "+layer.id+" has no brightness value", errorMessagePtr, datapointPtr);
            break;
        case Filter::Type::SKETCH_COLOR_ADJUSTMENT:
        case Filter::Type::FIGMA_COLOR_ADJUSTMENT:
            if (!filter.colorAdjustment.has_value())
                return validationError(&filter.colorAdjustment, "Color adjustment filter within layer "+layer.id+" has no colorAdjustment object", errorMessagePtr, datapointPtr);
            break;
    }
    if (
        (filter.type != Filter::Type::OPACITY_MULTIPLIER && filter.opacity.has_value()) ||
        ((filter.type != Filter::Type::XD_BRIGHTNESS_ADJUSTMENT && filter.type != Filter::Type::SKETCH_BRIGHTNESS_ADJUSTMENT) && filter.brightness.has_value()) ||
        ((filter.type != Filter::Type::SKETCH_COLOR_ADJUSTMENT && filter.type != Filter::Type::FIGMA_COLOR_ADJUSTMENT) && filter.colorAdjustment.has_value())
    )
        return validationError(&filter, "Filter within layer "+layer.id+" contains data that does not match its type", errorMessagePtr, datapointPtr);
    return true;
}

bool validateFill(const Layer &layer, const Fill &fill, std::string *errorMessagePtr, const void **datapointPtr) {
    if (fill.blendMode == BlendMode::PASS_THROUGH)
        return validationError(&fill.blendMode, "Fill within layer "+layer.id+" has invalid PASS_THROUGH blendMode", errorMessagePtr, datapointPtr);
    switch (fill.type) {
        case Fill::Type::COLOR:
            if (!fill.color.has_value())
                return validationError(&fill.color, "COLOR fill within layer "+layer.id+" has no color object", errorMessagePtr, datapointPtr);
            if (!validateColor(fill.color.value()))
                return validationError(&fill.color, "COLOR fill within layer "+layer.id+" has invalid color value", errorMessagePtr, datapointPtr);
            break;
        case Fill::Type::GRADIENT:
            if (!fill.gradient.has_value())
                return validationError(&fill.gradient, "GRADIENT fill within layer "+layer.id+" has no gradient object", errorMessagePtr, datapointPtr);
            for (const Gradient::ColorStop &colorStop : fill.gradient->stops) {
                if (!(colorStop.position >= 0 && colorStop.position <= 1))
                    return validationError(&colorStop.position, "GRADIENT fill within layer "+layer.id+" contains invalid color stop position", errorMessagePtr, datapointPtr);
                if ((colorStop.interpolation == Gradient::Interpolation::POWER && colorStop.interpolation == Gradient::Interpolation::REVERSE_POWER) && !colorStop.interpolationParameter.has_value())
                    return validationError(&colorStop.position, "GRADIENT fill within layer "+layer.id+" contains color stop with missing interpolationParameter", errorMessagePtr, datapointPtr);
                if ((colorStop.interpolation != Gradient::Interpolation::POWER && colorStop.interpolation != Gradient::Interpolation::REVERSE_POWER) && colorStop.interpolationParameter.has_value())
                    return validationError(&colorStop.position, "GRADIENT fill within layer "+layer.id+" contains color stop with invalid interpolationParameter", errorMessagePtr, datapointPtr);
                if (!validateColor(colorStop.color))
                    return validationError(&colorStop.color, "GRADIENT fill within layer "+layer.id+" contains color stop with invalid color value", errorMessagePtr, datapointPtr);
            }
            break;
        case Fill::Type::IMAGE:
            if (!fill.image.has_value())
                return validationError(&fill.image, "IMAGE fill within layer "+layer.id+" has no image object", errorMessagePtr, datapointPtr);
            break;
    }
    if (fill.filters.has_value()) {
        for (const Filter &filter : fill.filters.value()) {
            if (!validateFilter(layer, filter, errorMessagePtr, datapointPtr))
                return false;
        }
    }
    if (
        (fill.type != Fill::Type::COLOR && fill.color.has_value()) ||
        (fill.type != Fill::Type::GRADIENT && fill.gradient.has_value()) ||
        (fill.type != Fill::Type::IMAGE && (fill.image.has_value() || fill.filters.has_value()))
    )
        return validationError(&fill, "Fill within layer "+layer.id+" contains data that does not match its type", errorMessagePtr, datapointPtr);
    return true;
}

bool validateStroke(const Layer &layer, const Stroke &stroke, std::string *errorMessagePtr, const void **datapointPtr) {
    if (!validateFill(layer, stroke.fill, errorMessagePtr, datapointPtr))
        return false;
    if (stroke.thickness < 0)
        return validationError(&stroke.thickness, "Stroke within layer "+layer.id+" has negative thickness", errorMessagePtr, datapointPtr);
    return true;
}

bool validateStroke(const Layer &layer, const VectorStroke &stroke, std::string *errorMessagePtr, const void **datapointPtr) {
    if (!validateStroke(layer, static_cast<const Stroke &>(stroke), errorMessagePtr, datapointPtr))
        return false;
    if (stroke.dashing.has_value()) {
        for (double dash : stroke.dashing.value()) {
            if (dash <= 0)
                return validationError(&stroke.dashing, "Stroke within layer "+layer.id+" has invalid dashing", errorMessagePtr, datapointPtr);
        }
    }
    return true;
}

bool validateEffect(const Layer &layer, const Effect &effect, std::string *errorMessagePtr, const void **datapointPtr) {
    if (effect.blendMode == BlendMode::PASS_THROUGH && !(effect.type == Effect::Type::OVERLAY || effect.type == Effect::Type::STROKE))
        return validationError(&effect.blendMode, "Effect of layer "+layer.id+" has invalid PASS_THROUGH blendMode", errorMessagePtr, datapointPtr);
    switch (effect.type) {
        case Effect::Type::OVERLAY:
            if (!effect.overlay.has_value())
                return validationError(&effect.overlay, "OVERLAY effect of layer "+layer.id+" has no overlay object", errorMessagePtr, datapointPtr);
            if (!validateFill(layer, effect.overlay.value(), errorMessagePtr, datapointPtr))
                return false;
            break;
        case Effect::Type::STROKE:
            if (!effect.stroke.has_value())
                return validationError(&effect.stroke, "STROKE effect of layer "+layer.id+" has no stroke object", errorMessagePtr, datapointPtr);
            if (!validateStroke(layer, effect.stroke.value(), errorMessagePtr, datapointPtr))
                return false;
            break;
        case Effect::Type::DROP_SHADOW:
        case Effect::Type::INNER_SHADOW:
            if (!effect.shadow.has_value())
                return validationError(&effect.shadow, "Shadow effect of layer "+layer.id+" has no shadow object", errorMessagePtr, datapointPtr);
            if (effect.shadow->blur < 0)
                return validationError(&effect.shadow->blur, "Shadow effect of layer "+layer.id+" has negative blur", errorMessagePtr, datapointPtr);
            if (!validateColor(effect.shadow->color))
                return validationError(&effect.shadow->color, "Shadow effect of layer "+layer.id+" has invalid color value", errorMessagePtr, datapointPtr);
            break;
        case Effect::Type::OUTER_GLOW:
        case Effect::Type::INNER_GLOW:
            if (!effect.glow.has_value())
                return validationError(&effect.glow, "Glow effect of layer "+layer.id+" has no glow object", errorMessagePtr, datapointPtr);
            if (effect.glow->offset.x || effect.glow->offset.y)
                return validationError(&effect.glow, "Glow effect of layer "+layer.id+" has offset", errorMessagePtr, datapointPtr);
            if (effect.glow->blur < 0)
                return validationError(&effect.glow->blur, "Glow effect of layer "+layer.id+" has negative blur", errorMessagePtr, datapointPtr);
            if (!validateColor(effect.glow->color))
                return validationError(&effect.glow->color, "Glow effect of layer "+layer.id+" has invalid color value", errorMessagePtr, datapointPtr);
            break;
        case Effect::Type::GAUSSIAN_BLUR:
        case Effect::Type::BOUNDED_BLUR:
        case Effect::Type::BLUR:
            if (!effect.blur.has_value())
                return validationError(&effect.blur, "Blur effect of layer "+layer.id+" has no blur parameter", errorMessagePtr, datapointPtr);
            if (effect.blur.value() < 0)
                return validationError(&effect.blur, "Blur effect of layer "+layer.id+" has negative blur parameter", errorMessagePtr, datapointPtr);
            if (effect.filters.has_value()) {
                for (const Filter &filter : effect.filters.value()) {
                    if (!validateFilter(layer, filter, errorMessagePtr, datapointPtr))
                        return false;
                }
            }
            if (layer.blendMode == BlendMode::PASS_THROUGH && effect.basis != EffectBasis::BACKGROUND)
                return validationError(&effect, "Layer "+layer.id+" with PASS_THROUGH blendMode contains a non-background blur effect", errorMessagePtr, datapointPtr);
            break;
        case Effect::Type::OTHER:
            break;
    }
    switch (effect.basis) {
        case EffectBasis::BODY:
        case EffectBasis::BODY_AND_STROKES:
            if (isBlur(effect.type))
                return validationError(&effect.basis, "Layer "+layer.id+" has blur effect with invalid basis", errorMessagePtr, datapointPtr);
            break;
        case EffectBasis::FILL:
            break;
        case EffectBasis::LAYER_AND_EFFECTS:
        case EffectBasis::BACKGROUND:
            if (!isBlur(effect.type))
                return validationError(&effect.basis, "Layer "+layer.id+" has effect with invalid basis - only blur effects may have LAYER_AND_EFFECTS or BACKGROUND basis", errorMessagePtr, datapointPtr);
            break;
    }
    if (!isBlur(effect.type) && effect.filters.has_value())
        return validationError(&effect.filters, "Effect of layer "+layer.id+" contains filters array but is not of a blur type", errorMessagePtr, datapointPtr);
    if (
        (effect.type != Effect::Type::OVERLAY && effect.overlay.has_value()) ||
        (effect.type != Effect::Type::STROKE && effect.stroke.has_value()) ||
        ((effect.type != Effect::Type::DROP_SHADOW && effect.type != Effect::Type::INNER_SHADOW) && effect.shadow.has_value()) ||
        ((effect.type != Effect::Type::OUTER_GLOW && effect.type != Effect::Type::INNER_GLOW) && effect.glow.has_value()) ||
        (!isBlur(effect.type) && effect.blur.has_value())
    )
        return validationError(&effect, "Effect of layer "+layer.id+" contains data that does not match its type", errorMessagePtr, datapointPtr);
    return true;
}

bool validatePath(const Layer &layer, const Path &path, std::string *errorMessagePtr, const void **datapointPtr) {
    switch (path.type) {
        case Path::Type::PATH:
            if (!path.geometry.has_value())
                return validationError(&path.geometry, "Path component of type PATH within layer "+layer.id+" has no geometry", errorMessagePtr, datapointPtr);
            // TODO validate geometry, count vertices and check cornerRadii length
            if (path.cornerRadii.has_value()) {
                for (double r : path.cornerRadii.value()) {
                    if (r < 0)
                        return validationError(&path.cornerRadii, "Path component within layer "+layer.id+" has negative corner radius", errorMessagePtr, datapointPtr);
                }
            }
            break;
        case Path::Type::RECTANGLE:
            if (!path.rectangle.has_value())
                return validationError(&path.rectangle, "Path component of type RECTANGLE within layer "+layer.id+" has no rectangle bounds", errorMessagePtr, datapointPtr);
            if (path.cornerRadius.has_value() && path.cornerRadius.value() < 0)
                return validationError(&path.cornerRadius, "Path component within layer "+layer.id+" has negative corner radius", errorMessagePtr, datapointPtr);
            break;
        case Path::Type::COMPOUND:
            if (!path.paths.has_value())
                return validationError(&path.paths, "Path component of type COMPOUND within layer "+layer.id+" has no paths array", errorMessagePtr, datapointPtr);
            break;
    }
    if (
        (path.type != Path::Type::PATH && path.cornerRadii.has_value()) ||
        (path.type != Path::Type::RECTANGLE && (path.rectangle.has_value() || path.cornerRadius.has_value())) ||
        (path.type != Path::Type::COMPOUND && (path.op.has_value() || path.paths.has_value())) ||
        (path.type != Path::Type::PATH && path.type != Path::Type::COMPOUND && path.geometry.has_value())
    )
        return validationError(&path, "Path component within layer "+layer.id+" contains data that does not match its type", errorMessagePtr, datapointPtr);
    if (path.paths.has_value()) {
        for (const Path &child : path.paths.value()) {
            if (!validatePath(layer, child, errorMessagePtr, datapointPtr))
                return false;
        }
    }
    return true;
}

bool validateShape(const Layer &layer, const Shape &shape, std::string *errorMessagePtr, const void **datapointPtr) {
    if (shape.path.has_value()) {
        if (!validatePath(layer, shape.path.value(), errorMessagePtr, datapointPtr))
            return false;
    }
    for (const Fill &fill : shape.fills) {
        if (!validateFill(layer, fill, errorMessagePtr, datapointPtr))
            return false;
    }
    for (const Shape::Stroke &stroke : shape.strokes) {
        if (stroke.path.has_value()) {
            if (!validatePath(layer, stroke.path.value(), errorMessagePtr, datapointPtr))
                return false;
        }
        if (!validateStroke(layer, stroke, errorMessagePtr, datapointPtr))
            return false;
    }
    return true;
}

bool validateText(const Layer &layer, const Text &text, std::string *errorMessagePtr, const void **datapointPtr) {
    // TODO implement
    return true;
}

bool validateLayerChange(const Layer &layer, const LayerChange &layerChange, std::string *errorMessagePtr, const void **datapointPtr) {
    // TODO implement
    return true;
}

std::string randomLayerId() {
    std::string id;
    for (int i = 0; i < 16; ++i)
        id.push_back("0123456789abcdefghijklmnopqrstuvwxyz----"[rand()%36]);
    return id;
}

bool validate(Layer &layer, std::set<std::string> &layerIdSet, std::string *errorMessagePtr, const void **datapointPtr) {
    if (layer.id.empty())
        return validationError(&layer.id, "Layer id must not be empty", errorMessagePtr, datapointPtr);
    if (!validateLayerId(layer.id))
        layer.id = randomLayerId();
    if (!layerIdSet.insert(layer.id).second)
        return validationError(&layer.id, "Duplicate layer id: "+layer.id, errorMessagePtr, datapointPtr);
    if (!(layer.opacity >= 0 && layer.opacity <= 1))
        layer.opacity = 1;
    if (layer.featureScale.has_value()) {
        if (layer.featureScale.value() <= 0)
            layer.featureScale = 1;
    }
    switch (layer.type) {
        case Layer::Type::SHAPE:
            if (!layer.shape.has_value())
                return validationError(&layer.shape, "Missing shape in SHAPE layer "+layer.id, errorMessagePtr, datapointPtr);
            if (!validateShape(layer, layer.shape.value(), errorMessagePtr, datapointPtr))
                return false;
            break;
        case Layer::Type::TEXT:
            if (!layer.text.has_value())
                return validationError(&layer.text, "Missing text in TEXT layer "+layer.id, errorMessagePtr, datapointPtr);
            if (!validateText(layer, layer.text.value(), errorMessagePtr, datapointPtr))
                return false;
            if (layer.blendMode == BlendMode::PASS_THROUGH)
                layer.blendMode = BlendMode::NORMAL;
            break;
        case Layer::Type::GROUP:
            break;
        case Layer::Type::MASK_GROUP:
            if (!layer.mask.has_value()) {
                layer.type = Layer::Type::GROUP;
                break;
            }
            if (!layer.maskBasis.has_value())
                layer.maskBasis = MaskBasis::BODY;
            if ((layer.maskBasis.value() == MaskBasis::BODY_EMBED || layer.maskBasis.value() == MaskBasis::FILL_EMBED) && layer.maskChannels.has_value()) {
                if (!(layer.maskChannels.value()[0] == 0 && layer.maskChannels.value()[1] == 0 && layer.maskChannels.value()[2] == 0 && layer.maskChannels.value()[3] == 1 && layer.maskChannels.value()[4] == 0))
                    layer.maskChannels = { };
            }
            break;
        case Layer::Type::COMPONENT_REFERENCE:
            if (!(layer.componentId.has_value() && !layer.componentId.value().empty()))
                return validationError(&layer.componentId, "Empty componentId of COMPONENT_REFERENCE layer "+layer.id, errorMessagePtr, datapointPtr);
            // fallthrough
        case Layer::Type::COMPONENT_INSTANCE:
            if (layer.overrides.has_value()) {
                for (const Override &override : layer.overrides.value()) {
                    if (override.target.empty())
                        return validationError(&override.target, "Empty override target in layer "+layer.id, errorMessagePtr, datapointPtr);
                    for (const LayerChange &layerChange : override.changes) {
                        if (!validateLayerChange(layer, layerChange, errorMessagePtr, datapointPtr))
                            return false;
                    }
                }
            }
            break;
    }
    /*if (
        (layer.type != Layer::Type::SHAPE && layer.shape.has_value()) ||
        (layer.type != Layer::Type::TEXT && layer.text.has_value()) ||
        (layer.type != Layer::Type::MASK_GROUP && (layer.mask.has_value() || layer.maskBasis.has_value() || layer.maskChannels.has_value())) ||
        ((layer.type != Layer::Type::GROUP && layer.type != Layer::Type::MASK_GROUP && layer.type != Layer::Type::COMPONENT_INSTANCE) && layer.layers.has_value()) ||
        ((layer.type != Layer::Type::COMPONENT_REFERENCE && layer.type != Layer::Type::COMPONENT_INSTANCE) && (layer.componentId.has_value() || layer.overrides.has_value()))
    )
        return validationError(&layer, "Layer "+layer.id+" contains data that does not match its type", errorMessagePtr, datapointPtr);*/
    for (const Effect &effect : layer.effects) {
        if (!validateEffect(layer, effect, errorMessagePtr, datapointPtr))
            return false;
    }
    if (layer.mask.has_value()) {
        if (!validate(*layer.mask, layerIdSet, errorMessagePtr, datapointPtr))
            return false;
    }
    if (layer.layers.has_value()) {
        for (Layer &child : layer.layers.value()) {
            if (!validate(child, layerIdSet, errorMessagePtr, datapointPtr))
                return false;
        }
    }
    return true;
}

bool validate(Octopus &document, std::set<std::string> &layerIdSet, std::string *errorMessagePtr, const void **datapointPtr) {
    if (document.type != Octopus::Type::OCTOPUS_COMPONENT)
        return validationError(&document.type, "Type must be OCTOPUS_COMPONENT", errorMessagePtr, datapointPtr);
    if (document.dimensions.has_value()) {
        if (!(document.dimensions->width > 0 && document.dimensions->height > 0))
            return validationError(&document.dimensions, "Octopus dimensions must be positive", errorMessagePtr, datapointPtr);
    }
    if (document.content.has_value()) {
        if (!validate(*document.content, layerIdSet, errorMessagePtr, datapointPtr))
            return false;
    }
    return true;
}

}

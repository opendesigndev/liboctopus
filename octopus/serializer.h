
// Generated by json-cpp-gen by Viktor Chlumsky
// https://github.com/Chlumsky/json-cpp-gen

#pragma once

#include <nonstd/serialize_float.hpp>
#include "octopus.h"

namespace octopus {

class Serializer {

public:
    struct Error {
        enum Type {
            OK,
            UNREPRESENTABLE_FLOAT_VALUE,
            UNKNOWN_ENUM_VALUE
        } type;
        const void *datapoint;

        inline Error(Type type = Error::OK) : type(type), datapoint() { }
        inline Error(Type type, const void *datapoint) : type(type), datapoint(datapoint) { }
        operator Type() const;
        operator bool() const;
        const char *typeString() const;
    };

    static Error serialize(std::string &jsonString, const octopus::Octopus &input);
    static Error serialize(std::string &jsonString, const octopus::Layer &input);
    static Error serialize(std::string &jsonString, const octopus::LayerChange &input);

protected:
    std::string &json;

    Serializer(std::string &json);
    void writeEscaped(char c);

    Error serializeOctopusOctopusType(const octopus::Octopus::Type &value);
    Error serializeStdString(const std::string &value);
    Error serializeDouble(const double &value);
    Error serializeOctopusDimensions(const octopus::Dimensions &value);
    Error serializeOctopusLayerType(const octopus::Layer::Type &value);
    Error serializeBool(const bool &value);
    Error serializeOctopusBlendMode(const octopus::BlendMode &value);
    Error serializeDouble_6(const double value[6]);
    Error serializeOctopusShapeFillRule(const octopus::Shape::FillRule &value);
    Error serializeOctopusPathType(const octopus::Path::Type &value);
    Error serializeOctopusPathOp(const octopus::Path::Op &value);
    Error serializeStdVectorOctopusPath(const std::vector<octopus::Path> &value);
    Error serializeOctopusRectangle(const octopus::Rectangle &value);
    Error serializeStdVectorDouble(const std::vector<double> &value);
    Error serializeOctopusPath(const octopus::Path &value);
    Error serializeOctopusFillType(const octopus::Fill::Type &value);
    Error serializeOctopusColor(const octopus::Color &value);
    Error serializeOctopusGradientType(const octopus::Gradient::Type &value);
    Error serializeOctopusGradientInterpolation(const octopus::Gradient::Interpolation &value);
    Error serializeOctopusGradientColorStop(const octopus::Gradient::ColorStop &value);
    Error serializeStdVectorOctopusGradientColorStop(const std::vector<octopus::Gradient::ColorStop> &value);
    Error serializeOctopusGradient(const octopus::Gradient &value);
    Error serializeOctopusImageRefType(const octopus::ImageRef::Type &value);
    Error serializeOctopusImageRef(const octopus::ImageRef &value);
    Error serializeOctopusImage(const octopus::Image &value);
    Error serializeOctopusFillPositioningLayout(const octopus::Fill::Positioning::Layout &value);
    Error serializeOctopusFillPositioningOrigin(const octopus::Fill::Positioning::Origin &value);
    Error serializeOctopusFillPositioning(const octopus::Fill::Positioning &value);
    Error serializeOctopusFilterType(const octopus::Filter::Type &value);
    Error serializeOctopusColorAdjustment(const octopus::ColorAdjustment &value);
    Error serializeOctopusFilter(const octopus::Filter &value);
    Error serializeStdVectorOctopusFilter(const std::vector<octopus::Filter> &value);
    Error serializeOctopusFill(const octopus::Fill &value);
    Error serializeStdVectorOctopusFill(const std::vector<octopus::Fill> &value);
    Error serializeOctopusStrokePosition(const octopus::Stroke::Position &value);
    Error serializeOctopusVectorStrokeStyle(const octopus::VectorStroke::Style &value);
    Error serializeOctopusVectorStrokeLineJoin(const octopus::VectorStroke::LineJoin &value);
    Error serializeOctopusVectorStrokeLineCap(const octopus::VectorStroke::LineCap &value);
    Error serializeOctopusShapeStroke(const octopus::Shape::Stroke &value);
    Error serializeStdVectorOctopusShapeStroke(const std::vector<octopus::Shape::Stroke> &value);
    Error serializeOctopusShape(const octopus::Shape &value);
    Error serializeOctopusFont(const octopus::Font &value);
    Error serializeInt(const int &value);
    Error serializeOctopusOpenTypeFeature(const octopus::OpenTypeFeature &value);
    Error serializeStdVectorOctopusOpenTypeFeature(const std::vector<octopus::OpenTypeFeature> &value);
    Error serializeOctopusTextStyleLigatures(const octopus::TextStyle::Ligatures &value);
    Error serializeOctopusTextStyleUnderline(const octopus::TextStyle::Underline &value);
    Error serializeOctopusTextStyleLetterCase(const octopus::TextStyle::LetterCase &value);
    Error serializeOctopusVectorStroke(const octopus::VectorStroke &value);
    Error serializeStdVectorOctopusVectorStroke(const std::vector<octopus::VectorStroke> &value);
    Error serializeOctopusTextStyle(const octopus::TextStyle &value);
    Error serializeOctopusStyleRangeRange(const octopus::StyleRange::Range &value);
    Error serializeStdVectorOctopusStyleRangeRange(const std::vector<octopus::StyleRange::Range> &value);
    Error serializeOctopusStyleRange(const octopus::StyleRange &value);
    Error serializeStdVectorOctopusStyleRange(const std::vector<octopus::StyleRange> &value);
    Error serializeOctopusTextFrameMode(const octopus::TextFrame::Mode &value);
    Error serializeOctopusTextFrame(const octopus::TextFrame &value);
    Error serializeOctopusTextHorizontalAlign(const octopus::Text::HorizontalAlign &value);
    Error serializeOctopusTextVerticalAlign(const octopus::Text::VerticalAlign &value);
    Error serializeOctopusTextBaselinePolicy(const octopus::Text::BaselinePolicy &value);
    Error serializeOctopusTextOverflowPolicy(const octopus::Text::OverflowPolicy &value);
    Error serializeOctopusText(const octopus::Text &value);
    Error serializeOctopusMaskBasis(const octopus::MaskBasis &value);
    Error serializeStdArrayDouble5(const std::array<double, 5> &value);
    Error serializeStdListOctopusLayer(const std::list<octopus::Layer> &value);
    Error serializeStdVectorStdString(const std::vector<std::string> &value);
    Error serializeOctopusLayerChangeSubject(const octopus::LayerChange::Subject &value);
    Error serializeOctopusLayerChangeOp(const octopus::LayerChange::Op &value);
    Error serializeOctopusEffectType(const octopus::Effect::Type &value);
    Error serializeOctopusEffectBasis(const octopus::EffectBasis &value);
    Error serializeOctopusStroke(const octopus::Stroke &value);
    Error serializeOctopusVec2(const octopus::Vec2 &value);
    Error serializeOctopusShadow(const octopus::Shadow &value);
    Error serializeOctopusEffect(const octopus::Effect &value);
    Error serializeStdArrayDouble6(const std::array<double, 6> &value);
    Error serializeStdVectorOctopusEffect(const std::vector<octopus::Effect> &value);
    Error serializeOctopusLayerChangeValues(const octopus::LayerChange::Values &value);
    Error serializeOctopusLayerChange(const octopus::LayerChange &value);
    Error serializeStdVectorOctopusLayerChange(const std::vector<octopus::LayerChange> &value);
    Error serializeOctopusOverride(const octopus::Override &value);
    Error serializeStdVectorOctopusOverride(const std::vector<octopus::Override> &value);
    Error serializeOctopusLayer(const octopus::Layer &value);
    Error serializeOctopusOctopus(const octopus::Octopus &value);

private:
    template <typename U, typename T>
    void writeSigned(T value);

};

}

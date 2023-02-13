
#pragma once

#include "octopus.h"

namespace octopus {

// Generated by json-cpp-gen by Viktor Chlumsky
// https://github.com/Chlumsky/json-cpp-gen

class Serializer {

public:
    enum ErrorType {
        OK,
        UNREPRESENTABLE_FLOAT_VALUE,
        UNKNOWN_ENUM_VALUE,
    };

    struct Error {
        ErrorType type;
        const void *datapoint;

        inline Error(ErrorType type = ErrorType::OK) : type(type), datapoint() { }
        inline Error(ErrorType type, const void *datapoint) : type(type), datapoint(datapoint) { }
        operator ErrorType() const;
        operator bool() const;
        const char *typeString() const;
    };

    static Error serialize(std::string &jsonString, octopus::Octopus const &input);
    static Error serialize(std::string &jsonString, octopus::Layer const &input);

protected:
    std::string &json;

    Serializer(std::string &json);
    void write(char c);
    void write(const char *str);
    void writeEscaped(char c);

    Error serializeOctopusOctopusType(octopus::Octopus::Type const &value);
    Error serializeStdString(std::string const &value);
    Error serializeDouble(double const &value);
    Error serializeOctopusDimensions(octopus::Dimensions const &value);
    Error serializeOctopusLayerType(octopus::Layer::Type const &value);
    Error serializeBool(bool const &value);
    Error serializeOctopusBlendMode(octopus::BlendMode const &value);
    Error serializeDouble_6(double const value[6]);
    Error serializeOctopusShapeFillRule(octopus::Shape::FillRule const &value);
    Error serializeOctopusPathType(octopus::Path::Type const &value);
    Error serializeOctopusPathOp(octopus::Path::Op const &value);
    Error serializeStdVectorOctopusPath(std::vector<octopus::Path> const &value);
    Error serializeOctopusRectangle(octopus::Rectangle const &value);
    Error serializeStdVectorDouble(std::vector<double> const &value);
    Error serializeOctopusPath(octopus::Path const &value);
    Error serializeOctopusFillType(octopus::Fill::Type const &value);
    Error serializeOctopusColor(octopus::Color const &value);
    Error serializeOctopusGradientType(octopus::Gradient::Type const &value);
    Error serializeOctopusGradientInterpolation(octopus::Gradient::Interpolation const &value);
    Error serializeOctopusGradientColorStop(octopus::Gradient::ColorStop const &value);
    Error serializeStdVectorOctopusGradientColorStop(std::vector<octopus::Gradient::ColorStop> const &value);
    Error serializeOctopusGradient(octopus::Gradient const &value);
    Error serializeOctopusImageRefType(octopus::ImageRef::Type const &value);
    Error serializeOctopusImageRef(octopus::ImageRef const &value);
    Error serializeOctopusImage(octopus::Image const &value);
    Error serializeOctopusFillPositioningLayout(octopus::Fill::Positioning::Layout const &value);
    Error serializeOctopusFillPositioningOrigin(octopus::Fill::Positioning::Origin const &value);
    Error serializeOctopusFillPositioning(octopus::Fill::Positioning const &value);
    Error serializeOctopusFilterType(octopus::Filter::Type const &value);
    Error serializeOctopusColorAdjustment(octopus::ColorAdjustment const &value);
    Error serializeOctopusFilter(octopus::Filter const &value);
    Error serializeStdVectorOctopusFilter(std::vector<octopus::Filter> const &value);
    Error serializeOctopusFill(octopus::Fill const &value);
    Error serializeStdVectorOctopusFill(std::vector<octopus::Fill> const &value);
    Error serializeOctopusStrokePosition(octopus::Stroke::Position const &value);
    Error serializeOctopusVectorStrokeStyle(octopus::VectorStroke::Style const &value);
    Error serializeOctopusVectorStrokeLineJoin(octopus::VectorStroke::LineJoin const &value);
    Error serializeOctopusVectorStrokeLineCap(octopus::VectorStroke::LineCap const &value);
    Error serializeOctopusShapeStroke(octopus::Shape::Stroke const &value);
    Error serializeStdVectorOctopusShapeStroke(std::vector<octopus::Shape::Stroke> const &value);
    Error serializeOctopusShape(octopus::Shape const &value);
    Error serializeOctopusFont(octopus::Font const &value);
    Error serializeInt(int const &value);
    Error serializeOctopusOpenTypeFeature(octopus::OpenTypeFeature const &value);
    Error serializeStdVectorOctopusOpenTypeFeature(std::vector<octopus::OpenTypeFeature> const &value);
    Error serializeOctopusTextStyleLigatures(octopus::TextStyle::Ligatures const &value);
    Error serializeOctopusTextStyleUnderline(octopus::TextStyle::Underline const &value);
    Error serializeOctopusTextStyleLetterCase(octopus::TextStyle::LetterCase const &value);
    Error serializeOctopusVectorStroke(octopus::VectorStroke const &value);
    Error serializeStdVectorOctopusVectorStroke(std::vector<octopus::VectorStroke> const &value);
    Error serializeOctopusTextStyle(octopus::TextStyle const &value);
    Error serializeOctopusStyleRangeRange(octopus::StyleRange::Range const &value);
    Error serializeStdVectorOctopusStyleRangeRange(std::vector<octopus::StyleRange::Range> const &value);
    Error serializeOctopusStyleRange(octopus::StyleRange const &value);
    Error serializeStdVectorOctopusStyleRange(std::vector<octopus::StyleRange> const &value);
    Error serializeOctopusTextFrameMode(octopus::TextFrame::Mode const &value);
    Error serializeOctopusTextFrame(octopus::TextFrame const &value);
    Error serializeOctopusTextHorizontalAlign(octopus::Text::HorizontalAlign const &value);
    Error serializeOctopusTextVerticalAlign(octopus::Text::VerticalAlign const &value);
    Error serializeOctopusTextBaselinePolicy(octopus::Text::BaselinePolicy const &value);
    Error serializeOctopusTextOverflowPolicy(octopus::Text::OverflowPolicy const &value);
    Error serializeOctopusText(octopus::Text const &value);
    Error serializeOctopusMaskBasis(octopus::MaskBasis const &value);
    Error serializeStdArrayDouble5(std::array<double, 5> const &value);
    Error serializeStdListOctopusLayer(std::list<octopus::Layer> const &value);
    Error serializeStdVectorStdString(std::vector<std::string> const &value);
    Error serializeOctopusLayerChangeSubject(octopus::LayerChange::Subject const &value);
    Error serializeOctopusLayerChangeOp(octopus::LayerChange::Op const &value);
    Error serializeOctopusEffectType(octopus::Effect::Type const &value);
    Error serializeOctopusEffectBasis(octopus::EffectBasis const &value);
    Error serializeOctopusStroke(octopus::Stroke const &value);
    Error serializeOctopusVec2(octopus::Vec2 const &value);
    Error serializeOctopusShadow(octopus::Shadow const &value);
    Error serializeOctopusEffect(octopus::Effect const &value);
    Error serializeStdArrayDouble6(std::array<double, 6> const &value);
    Error serializeStdVectorOctopusEffect(std::vector<octopus::Effect> const &value);
    Error serializeStdVectorOctopusStroke(std::vector<octopus::Stroke> const &value);
    Error serializeOctopusLayerChangeValues(octopus::LayerChange::Values const &value);
    Error serializeOctopusLayerChange(octopus::LayerChange const &value);
    Error serializeStdVectorOctopusLayerChange(std::vector<octopus::LayerChange> const &value);
    Error serializeOctopusOverride(octopus::Override const &value);
    Error serializeStdVectorOctopusOverride(std::vector<octopus::Override> const &value);
    Error serializeOctopusLayer(octopus::Layer const &value);
    Error serializeOctopusOctopus(octopus::Octopus const &value);

private:
    template <typename U, typename T>
    void writeSigned(T value);

};

}
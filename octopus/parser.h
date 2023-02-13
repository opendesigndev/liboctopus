
#pragma once

#include "octopus.h"

namespace octopus {

// Generated by json-cpp-gen by Viktor Chlumsky
// https://github.com/Chlumsky/json-cpp-gen

class Parser {

public:
    enum ErrorType {
        OK,
        JSON_SYNTAX_ERROR,
        UNEXPECTED_END_OF_FILE,
        TYPE_MISMATCH,
        ARRAY_SIZE_MISMATCH,
        UNKNOWN_KEY,
        UNKNOWN_ENUM_VALUE,
        VALUE_OUT_OF_RANGE,
        STRING_EXPECTED,
        UTF16_ENCODING_ERROR,
    };

    struct Error {
        ErrorType type;
        int position;

        inline Error(ErrorType type = ErrorType::OK, int position = -1) : type(type), position(position) { }
        operator ErrorType() const;
        operator bool() const;
        const char *typeString() const;
    };

    static Error parse(octopus::Octopus &output, const char *jsonString);
    static Error parse(octopus::Layer &output, const char *jsonString);
    static Error parse(octopus::LayerChange &output, const char *jsonString);

protected:
    const char *cur;

    explicit Parser(const char *str);
    void skipWhitespace();
    ErrorType skipValue();
    bool matchSymbol(char s);
    ErrorType unescape(char *codepoints);
    static bool isAlphanumeric(char c);

    ErrorType parseStdString(std::string &value);
    ErrorType parseOctopusOctopusType(octopus::Octopus::Type &value);
    ErrorType parseDouble(double &value);
    ErrorType parseOctopusDimensions(octopus::Dimensions &value);
    ErrorType parseNonstdOptionalOctopusDimensions(nonstd::optional<octopus::Dimensions> &value);
    ErrorType parseOctopusLayerType(octopus::Layer::Type &value);
    ErrorType parseBool(bool &value);
    ErrorType parseOctopusBlendMode(octopus::BlendMode &value);
    ErrorType parseDouble_6(double value[6]);
    ErrorType parseNonstdOptionalDouble(nonstd::optional<double> &value);
    ErrorType parseOctopusShapeFillRule(octopus::Shape::FillRule &value);
    ErrorType parseNonstdOptionalOctopusShapeFillRule(nonstd::optional<octopus::Shape::FillRule> &value);
    ErrorType parseOctopusPathType(octopus::Path::Type &value);
    ErrorType parseOctopusPathOp(octopus::Path::Op &value);
    ErrorType parseNonstdOptionalOctopusPathOp(nonstd::optional<octopus::Path::Op> &value);
    ErrorType parseNonstdOptionalStdString(nonstd::optional<std::string> &value);
    ErrorType parseStdVectorOctopusPath(std::vector<octopus::Path> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusPath(nonstd::optional<std::vector<octopus::Path> > &value);
    ErrorType parseOctopusRectangle(octopus::Rectangle &value);
    ErrorType parseNonstdOptionalOctopusRectangle(nonstd::optional<octopus::Rectangle> &value);
    ErrorType parseStdVectorDouble(std::vector<double> &value);
    ErrorType parseNonstdOptionalStdVectorDouble(nonstd::optional<std::vector<double> > &value);
    ErrorType parseOctopusPath(octopus::Path &value);
    ErrorType parseNonstdOptionalOctopusPath(nonstd::optional<octopus::Path> &value);
    ErrorType parseOctopusFillType(octopus::Fill::Type &value);
    ErrorType parseOctopusColor(octopus::Color &value);
    ErrorType parseNonstdOptionalOctopusColor(nonstd::optional<octopus::Color> &value);
    ErrorType parseOctopusGradientType(octopus::Gradient::Type &value);
    ErrorType parseOctopusGradientInterpolation(octopus::Gradient::Interpolation &value);
    ErrorType parseOctopusGradientColorStop(octopus::Gradient::ColorStop &value);
    ErrorType parseStdVectorOctopusGradientColorStop(std::vector<octopus::Gradient::ColorStop> &value);
    ErrorType parseOctopusGradient(octopus::Gradient &value);
    ErrorType parseNonstdOptionalOctopusGradient(nonstd::optional<octopus::Gradient> &value);
    ErrorType parseOctopusImageRefType(octopus::ImageRef::Type &value);
    ErrorType parseOctopusImageRef(octopus::ImageRef &value);
    ErrorType parseOctopusImage(octopus::Image &value);
    ErrorType parseNonstdOptionalOctopusImage(nonstd::optional<octopus::Image> &value);
    ErrorType parseOctopusFillPositioningLayout(octopus::Fill::Positioning::Layout &value);
    ErrorType parseOctopusFillPositioningOrigin(octopus::Fill::Positioning::Origin &value);
    ErrorType parseOctopusFillPositioning(octopus::Fill::Positioning &value);
    ErrorType parseNonstdOptionalOctopusFillPositioning(nonstd::optional<octopus::Fill::Positioning> &value);
    ErrorType parseOctopusFilterType(octopus::Filter::Type &value);
    ErrorType parseOctopusColorAdjustment(octopus::ColorAdjustment &value);
    ErrorType parseNonstdOptionalOctopusColorAdjustment(nonstd::optional<octopus::ColorAdjustment> &value);
    ErrorType parseOctopusFilter(octopus::Filter &value);
    ErrorType parseStdVectorOctopusFilter(std::vector<octopus::Filter> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusFilter(nonstd::optional<std::vector<octopus::Filter> > &value);
    ErrorType parseOctopusFill(octopus::Fill &value);
    ErrorType parseStdVectorOctopusFill(std::vector<octopus::Fill> &value);
    ErrorType parseOctopusStrokePosition(octopus::Stroke::Position &value);
    ErrorType parseOctopusVectorStrokeStyle(octopus::VectorStroke::Style &value);
    ErrorType parseNonstdOptionalOctopusVectorStrokeStyle(nonstd::optional<octopus::VectorStroke::Style> &value);
    ErrorType parseOctopusVectorStrokeLineJoin(octopus::VectorStroke::LineJoin &value);
    ErrorType parseNonstdOptionalOctopusVectorStrokeLineJoin(nonstd::optional<octopus::VectorStroke::LineJoin> &value);
    ErrorType parseOctopusVectorStrokeLineCap(octopus::VectorStroke::LineCap &value);
    ErrorType parseNonstdOptionalOctopusVectorStrokeLineCap(nonstd::optional<octopus::VectorStroke::LineCap> &value);
    ErrorType parseOctopusShapeStroke(octopus::Shape::Stroke &value);
    ErrorType parseStdVectorOctopusShapeStroke(std::vector<octopus::Shape::Stroke> &value);
    ErrorType parseOctopusShape(octopus::Shape &value);
    ErrorType parseNonstdOptionalOctopusShape(nonstd::optional<octopus::Shape> &value);
    ErrorType parseNonstdOptionalBool(nonstd::optional<bool> &value);
    ErrorType parseOctopusFont(octopus::Font &value);
    ErrorType parseNonstdOptionalOctopusFont(nonstd::optional<octopus::Font> &value);
    ErrorType parseInt(int &value);
    ErrorType parseOctopusOpenTypeFeature(octopus::OpenTypeFeature &value);
    ErrorType parseStdVectorOctopusOpenTypeFeature(std::vector<octopus::OpenTypeFeature> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusOpenTypeFeature(nonstd::optional<std::vector<octopus::OpenTypeFeature> > &value);
    ErrorType parseOctopusTextStyleLigatures(octopus::TextStyle::Ligatures &value);
    ErrorType parseNonstdOptionalOctopusTextStyleLigatures(nonstd::optional<octopus::TextStyle::Ligatures> &value);
    ErrorType parseOctopusTextStyleUnderline(octopus::TextStyle::Underline &value);
    ErrorType parseNonstdOptionalOctopusTextStyleUnderline(nonstd::optional<octopus::TextStyle::Underline> &value);
    ErrorType parseOctopusTextStyleLetterCase(octopus::TextStyle::LetterCase &value);
    ErrorType parseNonstdOptionalOctopusTextStyleLetterCase(nonstd::optional<octopus::TextStyle::LetterCase> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusFill(nonstd::optional<std::vector<octopus::Fill> > &value);
    ErrorType parseOctopusVectorStroke(octopus::VectorStroke &value);
    ErrorType parseStdVectorOctopusVectorStroke(std::vector<octopus::VectorStroke> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusVectorStroke(nonstd::optional<std::vector<octopus::VectorStroke> > &value);
    ErrorType parseOctopusTextStyle(octopus::TextStyle &value);
    ErrorType parseOctopusStyleRangeRange(octopus::StyleRange::Range &value);
    ErrorType parseStdVectorOctopusStyleRangeRange(std::vector<octopus::StyleRange::Range> &value);
    ErrorType parseOctopusStyleRange(octopus::StyleRange &value);
    ErrorType parseStdVectorOctopusStyleRange(std::vector<octopus::StyleRange> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusStyleRange(nonstd::optional<std::vector<octopus::StyleRange> > &value);
    ErrorType parseOctopusTextFrameMode(octopus::TextFrame::Mode &value);
    ErrorType parseOctopusTextFrame(octopus::TextFrame &value);
    ErrorType parseNonstdOptionalOctopusTextFrame(nonstd::optional<octopus::TextFrame> &value);
    ErrorType parseOctopusTextHorizontalAlign(octopus::Text::HorizontalAlign &value);
    ErrorType parseOctopusTextVerticalAlign(octopus::Text::VerticalAlign &value);
    ErrorType parseOctopusTextBaselinePolicy(octopus::Text::BaselinePolicy &value);
    ErrorType parseOctopusTextOverflowPolicy(octopus::Text::OverflowPolicy &value);
    ErrorType parseOctopusText(octopus::Text &value);
    ErrorType parseNonstdOptionalOctopusText(nonstd::optional<octopus::Text> &value);
    ErrorType parseOctopusMaskBasis(octopus::MaskBasis &value);
    ErrorType parseNonstdOptionalOctopusMaskBasis(nonstd::optional<octopus::MaskBasis> &value);
    ErrorType parseStdArrayDouble5(std::array<double, 5> &value);
    ErrorType parseNonstdOptionalStdArrayDouble5(nonstd::optional<std::array<double, 5> > &value);
    ErrorType parseStdListOctopusLayer(std::list<octopus::Layer> &value);
    ErrorType parseNonstdOptionalStdListOctopusLayer(nonstd::optional<std::list<octopus::Layer> > &value);
    ErrorType parseStdVectorStdString(std::vector<std::string> &value);
    ErrorType parseOctopusLayerChangeSubject(octopus::LayerChange::Subject &value);
    ErrorType parseOctopusLayerChangeOp(octopus::LayerChange::Op &value);
    ErrorType parseNonstdOptionalInt(nonstd::optional<int> &value);
    ErrorType parseNonstdOptionalOctopusFill(nonstd::optional<octopus::Fill> &value);
    ErrorType parseNonstdOptionalOctopusVectorStroke(nonstd::optional<octopus::VectorStroke> &value);
    ErrorType parseOctopusEffectType(octopus::Effect::Type &value);
    ErrorType parseOctopusEffectBasis(octopus::EffectBasis &value);
    ErrorType parseOctopusStroke(octopus::Stroke &value);
    ErrorType parseNonstdOptionalOctopusStroke(nonstd::optional<octopus::Stroke> &value);
    ErrorType parseOctopusVec2(octopus::Vec2 &value);
    ErrorType parseOctopusShadow(octopus::Shadow &value);
    ErrorType parseNonstdOptionalOctopusShadow(nonstd::optional<octopus::Shadow> &value);
    ErrorType parseOctopusEffect(octopus::Effect &value);
    ErrorType parseNonstdOptionalOctopusEffect(nonstd::optional<octopus::Effect> &value);
    ErrorType parseNonstdOptionalOctopusFilter(nonstd::optional<octopus::Filter> &value);
    ErrorType parseNonstdOptionalOctopusBlendMode(nonstd::optional<octopus::BlendMode> &value);
    ErrorType parseStdArrayDouble6(std::array<double, 6> &value);
    ErrorType parseNonstdOptionalStdArrayDouble6(nonstd::optional<std::array<double, 6> > &value);
    ErrorType parseStdVectorOctopusEffect(std::vector<octopus::Effect> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusEffect(nonstd::optional<std::vector<octopus::Effect> > &value);
    ErrorType parseNonstdOptionalOctopusEffectBasis(nonstd::optional<octopus::EffectBasis> &value);
    ErrorType parseStdVectorOctopusStroke(std::vector<octopus::Stroke> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusStroke(nonstd::optional<std::vector<octopus::Stroke> > &value);
    ErrorType parseNonstdOptionalOctopusTextStyle(nonstd::optional<octopus::TextStyle> &value);
    ErrorType parseOctopusLayerChangeValues(octopus::LayerChange::Values &value);
    ErrorType parseOctopusLayerChange(octopus::LayerChange &value);
    ErrorType parseStdVectorOctopusLayerChange(std::vector<octopus::LayerChange> &value);
    ErrorType parseOctopusOverride(octopus::Override &value);
    ErrorType parseStdVectorOctopusOverride(std::vector<octopus::Override> &value);
    ErrorType parseNonstdOptionalStdVectorOctopusOverride(nonstd::optional<std::vector<octopus::Override> > &value);
    ErrorType parseOctopusLayer(octopus::Layer &value);
    ErrorType parseNonstdOptionalPtrOctopusLayer(nonstd::optional_ptr<octopus::Layer> &value);
    ErrorType parseOctopusOctopus(octopus::Octopus &value);

private:
    template <typename T>
    ErrorType readSigned(T &value);

};

}

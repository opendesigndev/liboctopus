
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>
#include "general.h"
#include "fill.h"
#include "stroke.h"

namespace octopus {

struct Font {
    std::string postScriptName;
    nonstd::optional<std::string> family;
    nonstd::optional<std::string> style;
    nonstd::optional<bool> syntheticPostScriptName;
};

struct OpenTypeFeature {
    std::string tag;
    int value = 0;
};

struct TextStyle {
    enum class Ligatures {
        NONE,
        STANDARD,
        ALL
    };
    enum class Underline {
        NONE,
        SINGLE,
        DOUBLE
    };
    enum class LetterCase {
        NONE,
        UPPERCASE,
        LOWERCASE,
        SMALL_CAPS,
        TITLE_CASE
    };
    nonstd::optional<Font> font;
    nonstd::optional<double> fontSize;
    nonstd::optional<double> lineHeight;
    nonstd::optional<double> letterSpacing;
    nonstd::optional<bool> kerning;
    nonstd::optional<std::vector<OpenTypeFeature> > features;
    nonstd::optional<Ligatures> ligatures;
    nonstd::optional<Underline> underline;
    nonstd::optional<bool> linethrough;
    nonstd::optional<LetterCase> letterCase;
    nonstd::optional<std::vector<Fill> > fills;
    nonstd::optional<std::vector<VectorStroke> > strokes;
};

struct StyleRange {
    struct Range {
        int from = 0;
        int to = 0;
    };
    TextStyle style;
    std::vector<Range> ranges;
};

struct TextFrame {
    enum class Mode {
        AUTO_WIDTH,
        AUTO_HEIGHT,
        FIXED
    };
    Mode mode = Mode::AUTO_WIDTH;
    nonstd::optional<Dimensions> size;
};

struct Text {
    enum class HorizontalAlign {
        LEFT,
        CENTER,
        RIGHT,
        JUSTIFY
    };
    enum class VerticalAlign {
        TOP,
        CENTER,
        BOTTOM
    };
    enum class BaselinePolicy {
        SET,
        CENTER,
        OFFSET_ASCENDER,
        OFFSET_BEARING
    };
    enum class OverflowPolicy {
        NO_OVERFLOW,
        CLIP_LINE,
        EXTEND_LINE,
        EXTEND_ALL
    };
    std::string value;
    TextStyle defaultStyle;
    nonstd::optional<std::vector<StyleRange> > styles;
    double transform[6] = { 1, 0, 0, 1, 0, 0 }; // TODO Transform transform;
    nonstd::optional<TextFrame> frame;
    HorizontalAlign horizontalAlign = HorizontalAlign::LEFT;
    VerticalAlign verticalAlign = VerticalAlign::TOP;
    BaselinePolicy baselinePolicy = BaselinePolicy::SET;
    OverflowPolicy overflowPolicy = OverflowPolicy::NO_OVERFLOW;
};

}

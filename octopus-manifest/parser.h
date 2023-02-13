
#pragma once

#include "octopus-manifest.h"

namespace octopus {

// Generated by json-cpp-gen by Viktor Chlumsky
// https://github.com/Chlumsky/json-cpp-gen

class ManifestParser {

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

    static Error parse(octopus::OctopusManifest &output, const char *jsonString);

protected:
    const char *cur;

    explicit ManifestParser(const char *str);
    void skipWhitespace();
    ErrorType skipValue();
    bool matchSymbol(char s);
    ErrorType unescape(char *codepoints);
    static bool isAlphanumeric(char c);

    ErrorType parseStdString(std::string &value);
    ErrorType parseOctopusOctopusManifestOrigin(octopus::OctopusManifest::Origin &value);
    ErrorType parseOctopusReferenceType(octopus::Reference::Type &value);
    ErrorType parseOctopusReference(octopus::Reference &value);
    ErrorType parseStdVectorOctopusReference(std::vector<octopus::Reference> &value);
    ErrorType parseNonstdOptionalStdString(nonstd::optional<std::string> &value);
    ErrorType parseOctopusPage(octopus::Page &value);
    ErrorType parseStdVectorOctopusPage(std::vector<octopus::Page> &value);
    ErrorType parseOctopusComponentRole(octopus::Component::Role &value);
    ErrorType parseDouble(double &value);
    ErrorType parseOctopusBounds(octopus::Bounds &value);
    ErrorType parseOctopusResourceLocationType(octopus::ResourceLocation::Type &value);
    ErrorType parseOctopusResourceLocation(octopus::ResourceLocation &value);
    ErrorType parseOctopusArtifactType(octopus::Artifact::Type &value);
    ErrorType parseOctopusArtifact(octopus::Artifact &value);
    ErrorType parseStdVectorOctopusArtifact(std::vector<octopus::Artifact> &value);
    ErrorType parseNonstdOptionalOctopusReference(nonstd::optional<octopus::Reference> &value);
    ErrorType parseNonstdOptionalOctopusResourceLocation(nonstd::optional<octopus::ResourceLocation> &value);
    ErrorType parseOctopusAssetFont(octopus::AssetFont &value);
    ErrorType parseStdVectorOctopusAssetFont(std::vector<octopus::AssetFont> &value);
    ErrorType parseOctopusAssetImage(octopus::AssetImage &value);
    ErrorType parseStdVectorOctopusAssetImage(std::vector<octopus::AssetImage> &value);
    ErrorType parseOctopusAssets(octopus::Assets &value);
    ErrorType parseNonstdOptionalOctopusAssets(nonstd::optional<octopus::Assets> &value);
    ErrorType parseOctopusComponentSet(octopus::ComponentSet &value);
    ErrorType parseStdMapStdStringStdString(std::map<std::string, std::string> &value);
    ErrorType parseOctopusComponentVariantMeta(octopus::Component::VariantMeta &value);
    ErrorType parseNonstdOptionalOctopusComponentVariantMeta(nonstd::optional<octopus::Component::VariantMeta> &value);
    ErrorType parseOctopusStatusValue(octopus::Status::Value &value);
    ErrorType parseInt(int &value);
    ErrorType parseStdVectorStdString(std::vector<std::string> &value);
    ErrorType parseOctopusStatusError(octopus::Status::Error &value);
    ErrorType parseNonstdOptionalOctopusStatusError(nonstd::optional<octopus::Status::Error> &value);
    ErrorType parseNonstdOptionalDouble(nonstd::optional<double> &value);
    ErrorType parseOctopusStatus(octopus::Status &value);
    ErrorType parseNonstdOptionalOctopusStatus(nonstd::optional<octopus::Status> &value);
    ErrorType parseOctopusComponent(octopus::Component &value);
    ErrorType parseStdVectorOctopusComponent(std::vector<octopus::Component> &value);
    ErrorType parseOctopusLibrary(octopus::Library &value);
    ErrorType parseStdVectorOctopusLibrary(std::vector<octopus::Library> &value);
    ErrorType parseOctopusChunkType(octopus::Chunk::Type &value);
    ErrorType parseOctopusChunk(octopus::Chunk &value);
    ErrorType parseStdVectorOctopusChunk(std::vector<octopus::Chunk> &value);
    ErrorType parseOctopusOctopusManifest(octopus::OctopusManifest &value);

private:
    template <typename T>
    ErrorType readSigned(T &value);

};

}
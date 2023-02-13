
#pragma once

#include <string>
#include <nonstd/optional.hpp>

namespace octopus {

struct ResourceLocation {
    enum class Type {
        RELATIVE,
        EXTERNAL
    };
    Type type;
    nonstd::optional<std::string> path;
    nonstd::optional<std::string> url;
    nonstd::optional<std::string> versionHash;
};

}

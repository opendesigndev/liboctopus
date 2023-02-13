
#pragma once

#include <string>
#include <vector>
#include <nonstd/optional.hpp>

namespace octopus {

struct Status {
    enum Value {
        READY,
        PENDING,
        PROCESSING,
        FAILED
    };
    struct Error {
        int code = 0;
        std::string message;
        std::vector<std::string> stacktrace;
    };
    Value value;
    nonstd::optional<Error> error;
    nonstd::optional<double> time;
};

}

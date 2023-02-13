
#pragma once

#include <string>
#include <vector>
#include "layer-change.h"

namespace octopus {

struct Override {
    std::vector<std::string> target;
    std::vector<LayerChange> changes;
};

}

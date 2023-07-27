
#include "fix-octopus.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(liboctopus) {
    emscripten::function("fixOctopus", &fixOctopus);
}
#endif

#include <vector>
#include <cctype>
#include <algorithm>

inline int levenshtein(const std::string &a, const std::string &b) {
    size_t n = b.size()+1, m = 1, k = 0;
    while (m <= n)
        m <<= 1;
    std::vector<int> d(m--);
    d[k] = 0;
    for (size_t i = 0; i < b.size(); ++i)
        ++k, d[k] = d[k-1]+1;
    for (size_t i = 0; i < a.size(); ++i) {
        int aEmpty = 1;
        ++k, d[k&m] = d[(k-n)&m]+aEmpty;
        for (size_t j = 0; j < b.size(); ++j) {
            ++k, d[k&m] = std::min(std::min(
                d[(k-1)&m]+1,
                d[(k-n)&m]+aEmpty),
                d[(k-n-1)&m]+!(toupper(a[i]) == toupper(b[j]))
            );
        }
    }
    return d[k&m];
}

#include "parser.h"
#include "serializer.h"
#include "validator.h"

std::string fixOctopus(const std::string &input) {
    std::string output;
    octopus::Octopus doc;
    std::set<std::string> layerIdSet;
    if (octopus::Parser::parse(doc, input.c_str()) || !octopus::validate(doc, layerIdSet) || octopus::Serializer::serialize(output, doc))
        return "";
    return output;
}

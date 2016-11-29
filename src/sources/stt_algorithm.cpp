
#include "stt_algorithm.h"

#include <regex>
#include <sstream>


StrVector algo::split(const std::string &str, const char delim) {
    StrVector result;
    std::string token;

    for_each(str.begin(), str.end(),
        [&](char c) {
            if (c != delim) {
                token += c;
            } else {
                if (token.length()) {
                    result.push_back(token);
                }
                token.clear();
            }
        });

    if (token.length()) {
        result.push_back(token);
    }

    return result;
}

std::string algo::join(const StrVector &strVec, const char delim) {
    std::string result;
    for (auto str : strVec) {
        result += str;
        result += delim;
    }

    return result.substr(0, result.size()-1);
}


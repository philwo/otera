//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_STRINGUTILS_H
#define OTERA_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

namespace otera {
    inline bool IsNumeric(const std::string &s) {
        try {
            std::stoll(s);
            return true;
        } catch (const std::invalid_argument &) {
            return false;
        }
    }

    // Trim functions from: https://stackoverflow.com/a/217605

    // Trim from start (in place).
    inline void TrimLeft(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // Trim from end (in place).
    inline void TrimRight(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // Trim from both ends (in place).
    inline void Trim(std::string &s) {
        TrimLeft(s);
        TrimRight(s);
    }
}

#endif //OTERA_STRINGUTILS_H

//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_STRINGUTILS_H
#define OTERA_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

namespace otera {
    // Trim functions from: https://stackoverflow.com/a/217605

    // trim from start (in place)
    inline void trim_left(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    inline void trim_right(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    inline void trim(std::string &s) {
        trim_left(s);
        trim_right(s);
    }
}

#endif //OTERA_STRINGUTILS_H

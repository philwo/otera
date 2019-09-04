// Copyright 2019 Philipp Wollermann. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

    // Trim functions are taken from: https://stackoverflow.com/a/217605

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

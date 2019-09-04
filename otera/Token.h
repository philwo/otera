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

#ifndef OTERA_TOKEN_H
#define OTERA_TOKEN_H

#include <string>

namespace otera {
    enum TokenKind {
        IDENTIFIER,
        STRING,
        INTEGER,
        EMPTY
    };

    class Token {
    public:
        Token() : kind(EMPTY), value("") {}
        Token(TokenKind kind, std::string value) : kind(kind), value(value) {}

        TokenKind getKind() const {
            return kind;
        }

        const std::string &getValue() const {
            return value;
        }

    private:
        TokenKind kind;
        std::string value;
    };
}


#endif //OTERA_TOKEN_H

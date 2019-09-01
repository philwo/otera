//
// Created by philwo on 9/1/19.
//

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

//
// Created by philwo on 9/1/19.
//

#include "otera/Template.h"
#include "otera/expressions/Expression.h"
#include "otera/expressions/ConstantExpression.h"
#include "otera/expressions/PrintParameterExpression.h"
#include "otera/StringUtils.h"
#include "otera/expressions/ProgramExpression.h"
#include "otera/expressions/ForEachExpression.h"
#include "otera/expressions/IfExpression.h"
#include "otera/Token.h"

#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

enum ParserState {
    // We're currently reading normal text.
            TEXT,
    // We read a '{' character and are now expecting either {{ ... }} or {# foreach item in array #}.
            COMMAND_STARTING,
    PRINT_COMMAND,
    PRINT_COMMAND_ENDING,
    COMPLEX_COMMAND,
    COMPLEX_COMMAND_ENDING,
};

otera::Template::Template(std::ifstream &stream) {
    std::stringstream input;
    input << stream.rdbuf();
    this->template_source = input.str();
}

std::string otera::Template::Render(const otera::Environment &env) {
    ParserState state = TEXT;
    std::stack<std::unique_ptr<Expression>> expression_stack;
    std::string buffer;

    expression_stack.push(std::make_unique<ProgramExpression>());

    int line = 0, column = 0;
    bool skip_next_newline = false;
    for (char &c : this->template_source) {
        // Track our current line and column in order to be able to print nice error messages.
        if (c == '\n') {
            line++;
            column = 0;
        } else {
            column++;
        }

        switch (state) {
            case TEXT:
                if (c == '{') {
                    state = COMMAND_STARTING;
                    std::unique_ptr<ConstantExpression> expr = std::make_unique<ConstantExpression>(std::move(buffer));
                    expression_stack.top()->AddChild(std::move(expr));
                    buffer.clear();
                } else if (c == '\n') {
                    if (!skip_next_newline) {
                        buffer.push_back(c);
                    }
                } else {
                    buffer.push_back(c);
                }
                skip_next_newline = false;
                break;
            case COMMAND_STARTING:
                if (c == '{') {
                    state = PRINT_COMMAND;
                } else if (c == '%') {
                    state = COMPLEX_COMMAND;
                } else {
                    state = TEXT;
                    buffer.push_back('{');
                    buffer.push_back(c);
                }
                break;
            case PRINT_COMMAND:
                if (c == '}') {
                    state = PRINT_COMMAND_ENDING;
                } else {
                    buffer.push_back(c);
                }
                break;
            case PRINT_COMMAND_ENDING:
                if (c == '}') {
                    state = TEXT;
                    otera::Trim(buffer);
                    std::unique_ptr<PrintParameterExpression> expr = std::make_unique<PrintParameterExpression>(
                            std::move(buffer));
                    expression_stack.top()->AddChild(std::move(expr));
                    buffer.clear();
                } else {
                    state = PRINT_COMMAND;
                    buffer.push_back(c);
                }
                break;
            case COMPLEX_COMMAND:
                if (c == '%') {
                    state = COMPLEX_COMMAND_ENDING;
                } else {
                    buffer.push_back(c);
                }
                break;
            case COMPLEX_COMMAND_ENDING:
                if (c == '}') {
                    state = TEXT;
                    otera::Trim(buffer);
                    std::vector<otera::Token> command_args = splitArgs(buffer);
                    if (command_args.size() == 0) {
                        throw "ERROR";
                    }

                    if (command_args[0].getKind() != IDENTIFIER) {
                        throw "ERROR";
                    }

                    if (command_args[0].getValue() == "foreach") {
                        std::unique_ptr<ForEachExpression> expr = std::make_unique<ForEachExpression>(command_args);
                        expression_stack.push(std::move(expr));
                    } else if (command_args[0].getValue() == "if") {
                        std::unique_ptr<IfExpression> expr = std::make_unique<IfExpression>(command_args);
                        expression_stack.push(std::move(expr));
                    } else if (command_args[0].getValue() == "end") {
                        if (expression_stack.size() == 1) {
                            throw "ERROR";
                        }
                        std::unique_ptr<Expression> expr = std::move(expression_stack.top());
                        expression_stack.pop();
                        expression_stack.top()->AddChild(std::move(expr));
                    }

                    buffer.clear();
                    skip_next_newline = true;
                } else {
                    state = COMPLEX_COMMAND;
                    buffer.push_back(c);
                }
                break;
        }
    }

    if (expression_stack.size() != 1) {
        throw "Unclosed commands found";
    }

    // Process any trailing text.
    std::unique_ptr<ConstantExpression> expr = std::make_unique<ConstantExpression>(std::move(buffer));
    expression_stack.top()->AddChild(std::move(expr));

    return expression_stack.top()->Execute(env);
}

std::vector<otera::Token> otera::Template::splitArgs(const std::string &buffer) const {
    std::stringstream bufstream(buffer);
    std::vector<otera::Token> command_args;
    while (bufstream.good()) {
        while (bufstream.peek() == ' ') {
            bufstream.get();
        }
        char next_char = bufstream.peek();
        bool next_token_is_quoted_string = next_char == '"';

        std::string token;
        bufstream >> std::quoted(token);

        if (token.empty()) {
            continue;
        } else if (next_token_is_quoted_string) {
            command_args.push_back(Token(STRING, token));
        } else if (otera::IsNumeric(token)) {
            command_args.push_back(Token(INTEGER, token));
        } else {
            command_args.push_back(Token(IDENTIFIER, token));
        }
    }
    return command_args;
}

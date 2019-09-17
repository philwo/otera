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

#include "IfExpression.h"

#include <stdexcept>

otera::IfExpression::IfExpression(std::vector<otera::Token> args) {
    if (args[0].getKind() != IDENTIFIER || args[0].getValue() != "if") {
        throw std::logic_error("IfExpression, but first arg is not 'if'");
    }

    if (args.size() != 4) {
        throw std::invalid_argument("`if` syntax error: needs exactly three arguments: {% if A <operator> B %}");
    }

    if (args[2].getKind() != IDENTIFIER) {
        throw std::invalid_argument("`if` syntax error: operator not valid (e.g. use ==, !=, >, <, ...)");
    }

    this->lhs_operand = args[1];
    this->op = args[2].getValue();
    this->rhs_operand = args[3];
}

void otera::IfExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

void otera::IfExpression::Execute(const otera::Environment &env, std::ostream &output_stream) {
    otera::Value lhs =
            this->lhs_operand.getKind() == IDENTIFIER ? env.GetParameter(this->lhs_operand.getValue()) : Value(
                    this->lhs_operand.getValue());
    otera::Value rhs =
            this->rhs_operand.getKind() == IDENTIFIER ? env.GetParameter(this->rhs_operand.getValue()) : Value(
                    this->rhs_operand.getValue());

    bool condition;
    if (op == "==") {
        condition = lhs == rhs;
    } else if (op == "!=") {
        condition = lhs != rhs;
    } else if (op == ">") {
        condition = lhs > rhs;
    } else if (op == "<") {
        condition = lhs < rhs;
    } else if (op == ">=") {
        condition = lhs >= rhs;
    } else if (op == "<=") {
        condition = lhs <= rhs;
    } else {
        throw std::invalid_argument("`if` syntax error: invalid operator '" + op + "'");
    }

    if (condition) {
        for (auto &&expr : this->children) {
            expr->Execute(env, output_stream);
        }
    }
}

std::string otera::IfExpression::GetCommandName() {
    return std::string("{% if ... %}");
}

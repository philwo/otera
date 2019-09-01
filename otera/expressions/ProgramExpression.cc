//
// Created by philwo on 9/1/19.
//

#include "ProgramExpression.h"

void otera::ProgramExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

std::string otera::ProgramExpression::Execute(const otera::Environment &env) {
    std::string result;
    for (auto&& expr : this->children) {
        result.append(expr->Execute(env));
    }
    return result;
}

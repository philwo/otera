//
// Created by philwo on 9/1/19.
//

#include "ConstantExpression.h"

void otera::ConstantExpression::AddChild(std::unique_ptr<Expression> expr) {
    throw "error";
}

std::string otera::ConstantExpression::Execute(const otera::Environment &env) {
    return this->text;
}

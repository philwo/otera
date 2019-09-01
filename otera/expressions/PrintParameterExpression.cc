//
// Created by philwo on 9/1/19.
//

#include "PrintParameterExpression.h"

void otera::PrintParameterExpression::AddChild(std::unique_ptr<Expression> expr) {
    throw "error";
}

std::string otera::PrintParameterExpression::Execute(const otera::Environment &env) {
    otera::Value value = env.GetParameter(this->name);
    return value.AsString();
}

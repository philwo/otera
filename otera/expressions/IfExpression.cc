//
// Created by philwo on 9/1/19.
//

#include "IfExpression.h"

otera::IfExpression::IfExpression(std::vector<std::string> args) {
    if (args[0] != "if" || args.size() != 4) {
        throw "ERROR";
    }

    this->lhs_operand = args[1];
    this->op = args[2];
    this->rhs_operand = args[3];
}

void otera::IfExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

std::string otera::IfExpression::Execute(const otera::Environment &env) {
    std::string result;

    otera::Value lhs = env.GetParameter(this->lhs_operand);
    otera::Value rhs(this->rhs_operand);

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
        throw "ERROR";
    }

    if (condition) {
        for (auto &&expr : this->children) {
            result.append(expr->Execute(env));
        }
    }

    return result;
}

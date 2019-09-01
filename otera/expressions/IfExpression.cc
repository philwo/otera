//
// Created by philwo on 9/1/19.
//

#include "IfExpression.h"

otera::IfExpression::IfExpression(std::vector<otera::Token> args) {
    if (args[0].getKind() != IDENTIFIER || args[0].getValue() != "if") {
        throw "ERROR";
    }

    if (args.size() != 4) {
        throw "ERROR";
    }

    if (args[2].getKind() != IDENTIFIER) {
        throw "ERROR";
    }

    this->lhs_operand = args[1];
    this->op = args[2].getValue();
    this->rhs_operand = args[3];
}

void otera::IfExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

std::string otera::IfExpression::Execute(const otera::Environment &env) {
    std::string result;

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
        throw "ERROR";
    }

    if (condition) {
        for (auto &&expr : this->children) {
            result.append(expr->Execute(env));
        }
    }

    return result;
}

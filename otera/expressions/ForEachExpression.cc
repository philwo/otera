//
// Created by philwo on 9/1/19.
//

#include "ForEachExpression.h"

otera::ForEachExpression::ForEachExpression(std::vector<otera::Token> args) {
    if (args[0].getKind() != IDENTIFIER || args[0].getValue() != "foreach") {
        throw "ERROR";
    }
    if (args[1].getKind() != IDENTIFIER || args[3].getKind() != IDENTIFIER) {
        throw "ERROR";
    }
    if (args[2].getKind() != IDENTIFIER || args[2].getValue() != "in") {
        throw "ERROR";
    }

    this->iterator_name = args[1].getValue();
    this->container_name = args[3].getValue();
}

void otera::ForEachExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

std::string otera::ForEachExpression::Execute(const otera::Environment &env) {
    std::string result;
    otera::Value container = env.GetParameter(this->container_name);

    for (auto&& item : container.AsList()) {
        otera::Environment env_with_loopvar(env);
        env_with_loopvar.SetParameter(this->iterator_name, item);
        for (auto &&expr : this->children) {
            result.append(expr->Execute(env_with_loopvar));
        }
    }

    return result;
}

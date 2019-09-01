//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_IFEXPRESSION_H
#define OTERA_IFEXPRESSION_H

#include "otera/expressions/Expression.h"
#include "otera/Token.h"

namespace otera {
    class IfExpression : public Expression {
    public:
        explicit IfExpression(std::vector<otera::Token> args);

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        std::vector<std::unique_ptr<Expression>> children;
        otera::Token lhs_operand;
        std::string op;
        otera::Token rhs_operand;
    };
}

#endif //OTERA_IFEXPRESSION_H

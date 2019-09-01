//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_IFEXPRESSION_H
#define OTERA_IFEXPRESSION_H

#include "otera/expressions/Expression.h"

namespace otera {
    class IfExpression : public Expression {
    public:
        explicit IfExpression(std::vector<std::string> args);

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        std::vector<std::unique_ptr<Expression>> children;
        std::string lhs_operand;
        bool lhs_operand_is_param_name;
        std::string op;
        std::string rhs_operand;
        bool rhs_operand_is_param_name;
    };
}

#endif //OTERA_IFEXPRESSION_H

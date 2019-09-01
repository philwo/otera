//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_CONSTANTEXPRESSION_H
#define OTERA_CONSTANTEXPRESSION_H

#include "otera/expressions/Expression.h"

namespace otera {
    class ConstantExpression : public Expression {
    public:
        ConstantExpression(std::string text) : text(text) {}

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        const std::string text;
    };
}

#endif //OTERA_CONSTANTEXPRESSION_H

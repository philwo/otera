//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_PRINTPARAMETEREXPRESSION_H
#define OTERA_PRINTPARAMETEREXPRESSION_H

#include "otera/expressions/Expression.h"

namespace otera {
    class PrintParameterExpression : public Expression {
    public:
        PrintParameterExpression(std::string name) : name(name) {}

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        const std::string name;
    };
}

#endif //OTERA_PRINTPARAMETEREXPRESSION_H

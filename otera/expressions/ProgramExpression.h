//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_PROGRAMEXPRESSION_H
#define OTERA_PROGRAMEXPRESSION_H

#include "otera/expressions/Expression.h"

namespace otera {
    class ProgramExpression : public Expression {
    public:
        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        std::vector<std::unique_ptr<Expression>> children;
    };
}

#endif //OTERA_PROGRAMEXPRESSION_H

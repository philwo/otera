//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_FOREACHEXPRESSION_H
#define OTERA_FOREACHEXPRESSION_H

#include "otera/expressions/Expression.h"

namespace otera {
    class ForEachExpression : public Expression {
    public:
        explicit ForEachExpression(std::vector<std::string> args);

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual std::string Execute(const otera::Environment &env) override;

    private:
        std::vector<std::unique_ptr<Expression>> children;
        std::string iterator_name;
        std::string container_name;
    };
}

#endif //OTERA_FOREACHEXPRESSION_H

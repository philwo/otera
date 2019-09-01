//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_EXPRESSION_H
#define OTERA_EXPRESSION_H

#include <memory>

#include "otera/Environment.h"

class Expression {
public:
    virtual ~Expression() {}

    virtual void AddChild(std::unique_ptr<Expression> expr) = 0;
    virtual std::string Execute(const otera::Environment &env) = 0;
};

#endif //OTERA_EXPRESSION_H

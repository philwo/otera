// Copyright 2019 Philipp Wollermann. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OTERA_FOREACHEXPRESSION_H
#define OTERA_FOREACHEXPRESSION_H

#include "otera/expressions/Expression.h"
#include "otera/Token.h"

namespace otera {
    class ForEachExpression : public Expression {
    public:
        explicit ForEachExpression(std::vector<otera::Token> args);

        std::string GetCommandName() override;

        virtual void AddChild(std::unique_ptr<Expression> expr) override;

        virtual void Execute(const otera::Environment &env, std::ostream &output_stream) override;

    private:
        std::vector<std::unique_ptr<Expression>> children;
        std::string iterator_name;
        std::string container_name;
    };
}

#endif //OTERA_FOREACHEXPRESSION_H

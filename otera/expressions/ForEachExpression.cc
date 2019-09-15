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

#include "ForEachExpression.h"

#include <stdexcept>

otera::ForEachExpression::ForEachExpression(std::vector<otera::Token> args) {
    if (args[0].getKind() != IDENTIFIER || args[0].getValue() != "foreach") {
        throw std::logic_error("ForEachExpression, but first arg is not 'foreach'");
    }

    if (args[1].getKind() != IDENTIFIER || args[3].getKind() != IDENTIFIER) {
        throw std::invalid_argument("`foreach` syntax error: must be {% foreach item in container %}");
    }

    if (args[2].getKind() != IDENTIFIER || args[2].getValue() != "in") {
        throw std::invalid_argument("`foreach` syntax error: must be {% foreach item in container %}");
    }

    this->iterator_name = args[1].getValue();
    this->container_name = args[3].getValue();
}

void otera::ForEachExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

void otera::ForEachExpression::Execute(const otera::Environment &env, std::ostream &output_stream) {
    otera::Value container = env.GetParameter(this->container_name);

    if (!container.IsIterable()) {
        throw std::invalid_argument("{% foreach " + this->iterator_name + " in " + this->container_name + " %}: container is not iterable");
    }

    for (auto&& item : container.AsList()) {
        otera::Environment env_with_loopvar(env);
        env_with_loopvar.SetParameter(this->iterator_name, item);
        for (auto &&expr : this->children) {
            expr->Execute(env_with_loopvar, output_stream);
        }
    }
}

std::string otera::ForEachExpression::GetCommandName() {
    return std::string("{% foreach ... %}");
}

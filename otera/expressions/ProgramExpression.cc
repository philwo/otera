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

#include "ProgramExpression.h"

void otera::ProgramExpression::AddChild(std::unique_ptr<Expression> expr) {
    this->children.push_back(std::move(expr));
}

void otera::ProgramExpression::Execute(const otera::Environment &env, std::ostream &output_stream) {
    for (auto&& expr : this->children) {
        expr->Execute(env, output_stream);
    }
}

std::string otera::ProgramExpression::GetCommandName() {
    return std::string("program");
}

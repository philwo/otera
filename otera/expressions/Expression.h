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

#ifndef OTERA_EXPRESSION_H
#define OTERA_EXPRESSION_H

#include <memory>

#include "otera/Environment.h"

class Expression {
public:
    virtual ~Expression() {}

    virtual void AddChild(std::unique_ptr<Expression> expr) = 0;
    virtual void Execute(const otera::Environment &env, std::ostream &output_stream) = 0;
    virtual std::string GetCommandName() = 0;
};

#endif //OTERA_EXPRESSION_H

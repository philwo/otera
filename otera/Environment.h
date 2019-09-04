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

#ifndef OTERA_ENVIRONMENT_H
#define OTERA_ENVIRONMENT_H

#include <unordered_map>

#include "otera/Value.h"

namespace otera {
    class Environment {
    public:
        /* Creates a new, empty environment. */
        Environment() {}

        /* Creates an environment as a copy of another one. */
        Environment(const Environment &old) : parameters(old.parameters) {}

        /* Sets the parameter named 'key' to the value 'value'. */
        void SetParameter(std::string key, Value value);

        /* Returns the parameter named 'key' or an empty value if the parameter does not exist. */
        Value GetParameter(std::string key) const;

    private:
        std::unordered_map<std::string, Value> parameters;
    };

    const Environment EmptyEnvironment = Environment();
}

#endif //OTERA_ENVIRONMENT_H

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

#ifndef OTERA_TEMPLATE_H
#define OTERA_TEMPLATE_H

#include <string>
#include <istream>
#include <memory>

#include "otera/Environment.h"
#include "otera/Token.h"

namespace otera {
    class Template {
    public:
        /*
         * Creates a new template.
         *
         * The template will be loaded from the given stream when calling the `Render` method.
         */
        explicit Template(std::unique_ptr<std::istream> stream);

        /*
         * Loads the template from the stream given to the constructor, renders it using parameters taken from the
         * given `env` and writes the output to the given `output_stream`.
         */
        void Render(const otera::Environment &env, std::ostream &output_stream);

        /*
         * This is a convenience wrapper that returns the rendered template directly as a string.
         */
        std::string Render(const otera::Environment &env);

    private:
        std::vector<otera::Token> splitArgs(const std::string &buffer) const;

        std::unique_ptr<std::istream> template_source;
    };
}

#endif //OTERA_TEMPLATE_H

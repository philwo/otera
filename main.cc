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

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "otera/Otera.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << argv[0] << " <input.txt>" << std::endl;
        return 1;
    }

    // Load our template from a file.
    std::unique_ptr<std::ifstream> input_file = std::make_unique<std::ifstream>(argv[1]);

    if (input_file->fail()) {
        std::cerr << "Could not open input file." << std::endl;
        return 1;
    }

    // Create an environment that holds our parameters.
    otera::Environment env;
    env.SetParameter("header", otera::Value("Hello world!"));
    env.SetParameter("somearray", otera::Value(
            std::vector<otera::Value>{otera::Value("Apple"), otera::Value("Banana"), otera::Value("Citrus")}));
    env.SetParameter("footer", otera::Value("That's it!"));

    // Load, parse and render the template into an output stream.
    std::stringstream result;
    otera::Template otmpl(std::move(input_file));
    try {
        otmpl.Render(env, result);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error while parsing template:" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Print the output.
    std::cout << result.str();

    return 0;
}

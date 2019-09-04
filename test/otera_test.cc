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

#include <iostream>
#include <fstream>
#include <sstream>

#include "gtest/gtest.h"
#include "otera/Otera.h"

TEST(OteraTest, FullExampleTest) {
    std::unique_ptr<std::ifstream> input_file = std::make_unique<std::ifstream>("test/data/example_input.txt");
    std::ifstream expected_output_file("test/data/example_output.txt");

    ASSERT_FALSE(input_file->fail()) << "file test/data/example_input.txt not found";
    ASSERT_FALSE(expected_output_file.fail()) << "file test/data/example_output.txt not found";

    otera::Environment env;
    env.SetParameter("header", otera::Value("Hello world!"));
    env.SetParameter("somearray", otera::Value(
            std::vector<otera::Value>{otera::Value("Apple"), otera::Value("Banana"), otera::Value("Citrus")}));
    env.SetParameter("footer", otera::Value("That's it!"));

    std::stringstream result;
    otera::Template otmpl(std::move(input_file));
    ASSERT_NO_THROW(otmpl.Render(env, result));

    std::stringstream expected_output;
    expected_output << expected_output_file.rdbuf();

    ASSERT_EQ(result.str(), expected_output.str());
}

TEST(OteraTest, ErrorMessageTest) {
    std::unique_ptr<std::ifstream> input_file = std::make_unique<std::ifstream>("test/data/failing_unknown_command.txt");

    ASSERT_FALSE(input_file->fail()) << "file test/data/failing_unknown_command.txt not found";

    otera::Environment env;
    otera::Template otmpl(std::move(input_file));
    std::stringstream result;

    try {
        otmpl.Render(env, result);
        FAIL() << "expected otmpl.Render to throw std::invalid_argument";
    } catch (const std::invalid_argument &e) {
        ASSERT_STREQ(e.what(), "3:14: unknown command: unknown");
    }
}

TEST(OteraTest, FailingForEachTest) {
    std::unique_ptr<std::ifstream> input_file = std::make_unique<std::ifstream>("test/data/failing_foreach.txt");

    ASSERT_FALSE(input_file->fail()) << "file test/data/failing_foreach.txt not found";

    otera::Environment env;
    otera::Template otmpl(std::move(input_file));
    std::stringstream result;

    try {
        otmpl.Render(env, result);
        FAIL() << "expected otmpl.Render to throw std::invalid_argument";
    } catch (const std::invalid_argument &e) {
        ASSERT_STREQ(e.what(), "{% foreach item in container %}: container is not iterable");
    }
}

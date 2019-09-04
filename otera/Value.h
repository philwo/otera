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

#ifndef OTERA_VALUE_H
#define OTERA_VALUE_H

#include <string>
#include <vector>

namespace otera {
    enum ValueKinds {
        SIMPLE,
        LIST
    };

    /*
     * `Value` is used to wrap data in a form that makes it easily usable by the template rendering engine.
     *
     * You can initialize a `Value` from either an integer, a string or an std::vector and put it into an
     * `otera::Environment` to be used as a parameter. Inside the template, you can then print this value
     * e.g. ({{ name }}), iterate over it (e.g. {% foreach item in vector %}) or use it in conditionals.
     */
    class Value {
    public:
        /*
         * Creates an empty Value.
         */
        Value() : kind(SIMPLE), simple_value(""), list_value() {}

        /*
         * Creates a copy of an existing Value.
         */
        Value(const Value &old) : kind(old.kind), simple_value(old.simple_value), list_value(old.list_value) {}

        /*
         * Creates a Value that holds an integer number.
         */
        explicit Value(long long value);

        /*
         * Creates a Value that holds a string.
         */
        explicit Value(std::string value);

        /*
         * Creates a Value that holds a list of Values (via std::vector).
         */
        explicit Value(std::vector<Value> value);

        /*
         * Returns whether this Value is numeric.
         */
        bool IsNumeric();

        /*
         * Returns whether this Value is iterable and can be used in {% foreach ... %} blocks.
         */
        bool IsIterable();

        /*
         * Returns the Value in a form that can be used for printing.
         */
        std::string AsString();

        /*
         * If this Value is iterable, returns the items that it is holding.
         */
        std::vector<Value> AsList();

        bool operator==(const Value &rhs) const;

        bool operator!=(const Value &rhs) const;

        bool operator<(const Value &rhs) const;

        bool operator>(const Value &rhs) const;

        bool operator<=(const Value &rhs) const;

        bool operator>=(const Value &rhs) const;

    private:
        ValueKinds kind;

        std::string simple_value;
        std::vector<Value> list_value;
    };

    const Value EmptyVariable = Value();
}

#endif //OTERA_VALUE_H

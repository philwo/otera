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

#include "otera/Value.h"
#include "otera/StringUtils.h"

#include <stdexcept>
#include <string>
#include <vector>

otera::Value::Value(long long value) {
    this->kind = SIMPLE;
    this->simple_value = std::to_string(value);
}

otera::Value::Value(std::string value) {
    this->kind = SIMPLE;
    this->simple_value = value;
}

otera::Value::Value(std::vector<Value> value) {
    this->kind = LIST;
    this->list_value = value;
}

bool otera::Value::IsNumeric() {
    return this->kind == SIMPLE && otera::IsNumeric(this->simple_value);
}

bool otera::Value::IsIterable() {
    return this->kind == LIST;
}

std::string otera::Value::AsString() {
    return this->simple_value;
}

std::vector<otera::Value> otera::Value::AsList() {
    return this->list_value;
}

bool otera::Value::operator==(const otera::Value &rhs) const {
    return kind == rhs.kind &&
           simple_value == rhs.simple_value &&
           list_value == rhs.list_value;
}

bool otera::Value::operator!=(const otera::Value &rhs) const {
    return !(rhs == *this);
}

bool otera::Value::operator<(const otera::Value &rhs) const {
    if (kind != SIMPLE || kind != rhs.kind) {
        return false;
    }

    try {
        return std::stoll(this->simple_value) < std::stoll(rhs.simple_value);
    } catch (const std::invalid_argument &) {
        return this->simple_value < rhs.simple_value;
    }
}

bool otera::Value::operator>(const otera::Value &rhs) const {
    return rhs < *this;
}

bool otera::Value::operator<=(const otera::Value &rhs) const {
    return !(rhs < *this);
}

bool otera::Value::operator>=(const otera::Value &rhs) const {
    return !(*this < rhs);
}

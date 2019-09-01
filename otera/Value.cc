//
// Created by philwo on 9/1/19.
//

#include "otera/Value.h"

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
    if (this->kind != SIMPLE) {
        return false;
    }

    try {
        std::stoll(this->simple_value);
        return true;
    } catch (const std::invalid_argument &) {
        return false;
    }
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

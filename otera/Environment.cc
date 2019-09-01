//
// Created by philwo on 9/1/19.
//

#include "Environment.h"

#include <fstream>

void otera::Environment::SetParameter(std::string key, Value value) {
    this->parameters[key] = value;
}

otera::Value otera::Environment::GetParameter(std::string key) const {
    auto el = this->parameters.find(key);

    if (el == this->parameters.end()) {
        return otera::EmptyVariable;
    } else {
        return el->second;
    }
}

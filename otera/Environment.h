//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_ENVIRONMENT_H
#define OTERA_ENVIRONMENT_H

#include <unordered_map>

#include "otera/Value.h"

namespace otera {
    class Environment {
    public:
        Environment() {}
        Environment(const Environment &old) : parameters(old.parameters) {}

        void SetParameter(std::string key, Value value);
        Value GetParameter(std::string key) const;

    private:
        std::unordered_map<std::string, Value> parameters;
    };

    const Environment EmptyEnvironment = Environment();
}

#endif //OTERA_ENVIRONMENT_H

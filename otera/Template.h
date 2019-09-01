//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_TEMPLATE_H
#define OTERA_TEMPLATE_H

#include <string>

#include "otera/Environment.h"

namespace otera {
    class Template {
    public:
        explicit Template(std::ifstream &stream);

        std::string Render() {
            return Render(otera::EmptyEnvironment);
        }

        std::string Render(const otera::Environment& env);

    private:
        std::vector<std::string> splitArgs(const std::string &buffer) const;

        std::string template_source;
    };
}

#endif //OTERA_TEMPLATE_H

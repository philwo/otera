//
// Created by philwo on 9/1/19.
//

#ifndef OTERA_VALUE_H
#define OTERA_VALUE_H

#include <string>
#include <vector>

namespace otera {
    enum ValueKinds {
        SIMPLE,
        LIST
    };

    class Value {
    public:
        Value() : kind(SIMPLE), simple_value(""), list_value() {}

        Value(const Value &old) : kind(old.kind), simple_value(old.simple_value), list_value(old.list_value) {}

        explicit Value(long long value);

        explicit Value(std::string value);

        explicit Value(std::vector<Value> value);

        bool IsNumeric();

        bool IsIterable();

        std::string AsString();

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

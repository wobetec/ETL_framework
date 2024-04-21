#pragma once

#include <string>
#include <variant>

#include "datetime.h"

typedef std::variant<
    // native C++ types
    int,
    bool,
    float,
    double,
    std::string,

    // custom types
    DateTime,
    TimeDelta
> DefaultObject;

struct PrintVisitor{
    template <typename T>
    void operator()(const T& value) const{
        std::cout << value;
    }
};

template <typename Op_T>
struct AddVisitor {
    template<typename T, typename U>
    Op_T operator()(const T& lhs, const U& rhs) const {
        return lhs + rhs;
    }
};
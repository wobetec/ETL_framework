#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
class DataFrame {
    public:
        virtual void print() = 0;
        virtual void append(T data) = 0;
        virtual int size() = 0;
};
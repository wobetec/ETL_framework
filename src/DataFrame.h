#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
class DataFrame {
    public:
        // print
        virtual void print() = 0;
        
        // insert
        virtual void append(T data) = 0;

        // metadata
        virtual int size() = 0;
        virtual std::string type() = 0;
};
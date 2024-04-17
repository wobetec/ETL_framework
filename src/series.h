#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <variant>

#include "default_object.h"

template <typename T>
class Series {
    public:
        Series() {}
        Series(std::vector<T> data) : data(data) {};

        void append(T value) {
            data.push_back(value);
        }

        Series<T> append(Series<T> &other) {
            Series <T> result = copy();
            for (T value : other.data) {
                result.append(value);
            }
            return result;
        }

        T operator[](int index) {
            return data[index];
        }

        template <typename U>
        Series<T> add(Series<T> &other) {
            if (shape() != other.shape()) {
                throw std::invalid_argument("Series must have the same size");
            }
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) + std::get<U>(other[i]));
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> add(U other) {
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) + other);
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> sub(Series<T> &other) {
            if (shape() != other.shape()) {
                throw std::invalid_argument("Series must have the same size");
            }
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) - std::get<U>(other[i]));
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> sub(U other) {
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) - other);
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> mul(Series<T> &other) {
            if (shape() != other.shape()) {
                throw std::invalid_argument("Series must have the same size");
            }
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) * std::get<U>(other[i]));
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> mul(U other) {
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) * other);
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> div(Series<T> &other) {
            if (shape() != other.shape()) {
                throw std::invalid_argument("Series must have the same size");
            }
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) / std::get<U>(other[i]));
            }
            return Series<T>(result);
        }

        template <typename U>
        Series<T> div(U other) {
            std::vector<T> result;
            for (int i = 0; i < data.size(); i++) {
                result.push_back(std::get<U>(data[i]) / other);
            }
            return Series<T>(result);
        }

        int shape() {
            return data.size();
        }

        void print() {
            int padding = 15;
            std::cout << std::right << std::setw(padding) << "Series" << std::endl;
            for (T value : data) {
                std::cout << std::right << std::setw(padding);
                std::visit(PrintVisitor{}, value);
                std::cout << std::endl;
            }
        }

        Series<T> copy() {
            return Series<T>(data);
        }

        template <typename U>
        Series<T> equal(U value) {
            std::vector<T> result;

            for (T v : data) {
                result.push_back(std::get<U>(v) == value);
            }
        
            return Series<T>(result);
        }

        template <typename U>
        Series<T> greater_equal(U value) {
            std::vector<T> result;

            for (T v : data) {
                result.push_back(std::get<U>(v) >= value);
            }
        
            return Series<T>(result);
        }

        template <typename U>
        Series<T> less_equal(U value) {
            std::vector<T> result;

            for (T v : data) {
                result.push_back(std::get<U>(v) <= value);
            }
        
            return Series<T>(result);
        }

        template <typename U>
        Series<T> greater(U value) {
            std::vector<T> result;

            for (T v : data) {
                result.push_back(std::get<U>(v) > value);
            }
        
            return Series<T>(result);
        }

        template <typename U>
        Series<T> less(U value) {
            std::vector<T> result;

            for (T v : data) {
                result.push_back(std::get<U>(v) < value);
            }
        
            return Series<T>(result);
        }


    private:
        std::vector<T> data;
};
#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <variant>
#include <type_traits>
#include <stdexcept>

#include "default_object.h"

template <typename T>
class Series {
    public:
        Series() {}
        Series(std::vector<T> data) : data(data) {};
        ~Series() {
            data.clear();
        }

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
        Series<T> compare(U value, std::string op) {
            std::vector<T> result;

            for (T v : data) {
                if (op == "==") {
                    result.push_back(std::get<U>(v) == value);
                } else if (op == ">=") {
                    result.push_back(std::get<U>(v) >= value);
                } else if (op == "<=") {
                    result.push_back(std::get<U>(v) <= value);
                } else if (op == ">") {
                    result.push_back(std::get<U>(v) > value);
                } else if (op == "<") {
                    result.push_back(std::get<U>(v) < value);
                } else {
                    throw std::invalid_argument("Invalid operator");
                }
            }
        }

        template <typename U, typename V>
        Series<T> astype() {
            std::vector<T> result;
            V value;
            for (T v : data) {
                if (std::is_same_v<U, std::string> && std::is_same_v<V, int>) {
                    value = std::stoi(std::get<U>(v));
                } else {
                    throw std::invalid_argument("Invalid conversion");
                }
                result.push_back(value);
            }
            return Series<T>(result);
        }

        Series<T> to_datetime() {
            std::vector<T> result;
            DateTime value;
            for (T v : data) {
                value = DateTime(std::get<std::string>(v));
                result.push_back(value);
            }
            return Series<T>(result);
        }

        std::vector<T> data;
    private:
};
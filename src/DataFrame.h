#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <variant>
#include <string>

#include "series.h"

template <typename T>
class DataFrame {
    public:
        DataFrame() {};

        void addColumn(std::string columnName, Series<T> new_serie) {

            if (shape.first != 0 && shape.first != new_serie.shape()) {
                throw std::invalid_argument("Series must have the same size");
            }
            
            int column = column_id(columnName);

            if (column == -1){
                columns.push_back(columnName);
                series.push_back(new_serie);
                shape.first = new_serie.shape();
                shape.second = series.size();
            } else {
                series[column] = new_serie;
            }
        }

        void print() {
            for (std::string column : columns) {
                std::cout << std::right << std::setw(15) << column;
            }

            std::cout << std::endl;

            for (int i = 0; i < shape.first; i++) {
                for (int j = 0; j < shape.second; j++) {
                    std::cout << std::right << std::setw(15);
                    std::visit(PrintVisitor{}, series[j][i]);
                }

                std::cout << std::endl;
            }
        }

        Series<T>& operator[](const std::string& columnName) {
            // Find the column in the existing columns
            int column = column_id(columnName);

            // If the column doesn't exist, create a new one
            if (column == -1) {
                columns.push_back(columnName);
                series.push_back(Series<T>());
                shape.first = series.back().shape();
                shape.second = series.size();
                return series.back();
            } else {
                // If the column exists, return the existing series
                return series[column];
            }
        }

        void dropSeries(std::string columnName) {
            int column = column_id(columnName);

            if (column == -1) {
                throw std::invalid_argument("Column does not exist");
            }

            columns.erase(columns.begin() + column);
            series.erase(series.begin() + column);
            shape.second = series.size();
        }

    private:
        std::vector<Series<T>> series;
        std::vector<std::string> columns;
        std::pair<int, int> shape;

        int column_id(std::string columnName) {
            for (int i = 0; i < columns.size(); i++) {
                if (columns[i] == columnName) {
                    return i;
                }
            }
            return -1;
        }
};
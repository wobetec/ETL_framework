#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <variant>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <set>

#include "series.h"

template <typename T>
class DataFrame {
    public:
        // Default constructor
        DataFrame() {};
        DataFrame(std::vector<std::string> columns, std::vector<Series<T>> series) {
            if (columns.size() != series.size()) {
                throw std::invalid_argument("Columns and series must have the same size");
            }

            for (int i = 0; i < columns.size(); i++) {
                addColumn(columns[i], series[i]);
            }

            shape.first = series[0].shape();
            shape.second = series.size();
        }
        DataFrame(std::map<std::string, Series<T>> data) {
            for (auto const& [key, val] : data) {
                addColumn(key, Series<T>(val));
            }
        }

        // Copy constructor
        DataFrame<T> copy() {
            return DataFrame<T>(columns, series);
        }

        // Destructor
        ~DataFrame() {
            series.clear();
            columns.clear();
        };

        // Print the DataFrame
        void print() {
            for (std::string column : columns) {
                std::cout << std::right << std::setw(30) << column;
            }

            std::cout << std::endl;

            for (int i = 0; i < shape.first; i++) {
                for (int j = 0; j < shape.second; j++) {
                    std::cout << std::right << std::setw(30);
                    std::visit(PrintVisitor{}, series[j][i]);
                }

                std::cout << std::endl;
            }
        }

        // Rename column
        void renameColumn(std::string oldName, std::string newName) {
            int column = column_id(oldName);

            if (column == -1) {
                throw std::invalid_argument("Column does not exist" + oldName);
            }

            columns[column] = newName;
        }
        
        // Add to the DataFrame
        void addColumn(std::string columnName, Series<T> newSeries) {

            if (shape.first != 0 && shape.first != newSeries.shape()) {
                std::cout << shape.first << " " << newSeries.shape() << std::endl;
                throw std::invalid_argument("New Column must have the same size as the DataFrame");
            }
            
            int column = column_id(columnName);

            if (column == -1){
                columns.push_back(columnName);
                series.push_back(newSeries);
                shape.first = newSeries.shape();
                shape.second = series.size();
            } else {
                series[column] = newSeries;
            }
        }

        void append(std::map<std::string, T> row) {
            if (shape.first == 0) {
                for (auto const& [key, val] : row) {
                    columns.push_back(key);
                    series.push_back(Series<T>());
                    series.back().append(val);
                }
                shape.first = 1;
                shape.second = series.size();
            } else {
                for (int i = 0; i < columns.size(); i++) {
                    series[i].append(row[columns[i]]);
                }
                shape.first++;
            }
        }

        // Defaults operators overloading
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

        DataFrame<T> operator[](const std::vector<std::string>& columnNames) {
            DataFrame<T> result;

            for (std::string column : columnNames) {
                int columnId = column_id(column);
                if (columnId == -1) {
                    throw std::invalid_argument("Column does not exist " + column);
                }
                result.addColumn(column, series[columnId]);
            }

            return result;
        }

        // Manipulation methods
        void dropColumn(std::string columnName) {
            /**
             * @brief Drop a column from the DataFrame
             * 
             * @param columnName The name of the column to drop
             */
            int column = column_id(columnName);

            if (column == -1) {
                throw std::invalid_argument("dropColumn: Column does not exist drop " + columnName);
            }

            columns.erase(columns.begin() + column);
            series.erase(series.begin() + column);
            shape.second = series.size();
        }

        DataFrame<T> concat(DataFrame<T> &other) {
            /**
             * @brief Simplesmente concatena dois dataframes que tenham as colunas na mesma ordem
             * 
             * @param other The DataFrame to concatenate
             * @return DataFrame<T> The concatenated DataFrame
             */
            DataFrame<T> result;
            
            for (int i = 0; i < columns.size(); i++) {
                Series<T> new_serie = series[i].append(other[columns[i]]);
                result.addColumn(columns[i], new_serie);
            }

            return result;
        }

        DataFrame<T> filter(Series<T> condition) {
            /**
             * @brief Filter the DataFrame based on a condition bool series
             * 
             * @param condition The condition to filter the DataFrame
             * @return DataFrame<T> The filtered DataFrame
             */

            if (condition.shape() != shape.first) {
                throw std::invalid_argument("Condition must have the same size");
            }

            DataFrame<T> result;
            for(std::string column : columns) {
                result.addColumn(column, Series<T>());
            }

            for (int i = 0; i < shape.first; i++) {
                if (std::get<bool>(condition[i])) {
                    for (int j = 0; j < shape.second; j++) {
                        result[columns[j]].append(series[j][i]);
                    }
                }
            }

            result.shape.first = result.series[0].shape();

            return result;
        }

        template <typename U>
        DataFrame<T> filter(std::string columnName, std::string condition, U value) {
            /**
             * @brief Filter the DataFrame based on a condition
             * 
             * @param columnName The column to apply the condition
             * @param condition Could be "==", "!=", ">", "<", ">=", "<="
             * @param value The value to compare
             * @return DataFrame<T> The filtered DataFrame
             */
            int column = column_id(columnName);

            if (column == -1) {
                throw std::invalid_argument("Column does not exist" + columnName);
            }

            DataFrame<T> result;
            for(std::string column : columns) {
                result.addColumn(column, Series<T>());
            }

            if (condition == "==") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) == value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else if (condition == "!=") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) != value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else if (condition == ">") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) > value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else if (condition == "<") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) < value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else if (condition == ">=") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) >= value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else if (condition == "<=") {
                for (int i = 0; i < shape.first; i++) {
                    if (std::get<U>(series[column][i]) <= value) {
                        for (int j = 0; j < shape.second; j++) {
                            result[columns[j]].append(series[j][i]);
                        }
                    }
                }
            } else {
                throw std::invalid_argument("Invalid condition");
            }
            
            result.shape.first = result.series[0].shape();

            return result;
        }

        template <typename U>
        DataFrame<T> sort(std::string columnName, bool ascending = true) {
            /**
             * @brief Sort the DataFrame based on a single column
             * 
             * @param columnName The column to sort
             * @param ascending If the sort is ascending or descending
             * @return DataFrame<T> The sorted DataFrame
             */
            int column = column_id(columnName);

            if (column == -1) {
                throw std::invalid_argument("Column does not exist" + columnName);
            }

            DataFrame<T> result;
            for(std::string column : columns) {
                result.addColumn(column, Series<T>());
            }

            std::vector<int> indexes;
            for (int i = 0; i < shape.first; i++) {
                indexes.push_back(i);
            }

            std::sort(indexes.begin(), indexes.end(), [&](int a, int b) {
                if (ascending) {
                    return std::get<U>(series[column][a]) < std::get<U>(series[column][b]);
                } else {
                    return std::get<U>(series[column][a]) > std::get<U>(series[column][b]);
                }
            });

            for (int i = 0; i < shape.first; i++) {
                for (int j = 0; j < shape.second; j++) {
                    result[columns[j]].append(series[j][indexes[i]]);
                }
            }

            result.shape.first = result.series[0].shape();

            return result;
        }

        template <typename U>
        DataFrame<T> merge(DataFrame<T> &other, std::string leftOn, std::string rightOn) {
            /**
             * @brief Merge two DataFrames based on a single column always with inner join
             * 
             * @param other The DataFrame to merge
             * @param leftOn The column to merge from the left DataFrame
             * @param rightOn The column to merge from the right DataFrame
             * @return DataFrame<T> The merged DataFrame
             */
            int leftColumn = column_id(leftOn);
            int rightColumn = other.column_id(rightOn);

            if (leftColumn == -1) {
                throw std::invalid_argument("DataFrame.merge: leftOn column does not exist " + leftOn);
            }
            if (rightColumn == -1) {
                throw std::invalid_argument("DataFrame.merge: rightOn column does not exist " + rightOn);
            }

            std::vector<std::string> rightColumns = other.columns;
            std::map<U, int> rightMap;
            std::set<U> rightSet;

            // gera o map
            for (int i = 0; i < other.shape.first; i++) {
                rightMap[std::get<U>(other[rightOn][i])] = i;
                rightSet.insert(std::get<U>(other[rightOn][i]));
            }

            // filtra os valores que existem nos dois dataframes
            std::vector<DefaultObject> leftMask;
            for (int i = 0; i < shape.first; i++) {
                if (rightSet.find(std::get<U>(series[leftColumn][i])) != rightSet.end()) {
                    leftMask.push_back(true);
                } else {
                    leftMask.push_back(false);
                }
            }
            DataFrame<T> result = filter(Series<DefaultObject>(leftMask));

            for(std::string column : rightColumns) {
                if (column == rightOn) {
                    continue;
                }
                std::vector<T> newColumn;
                for (int i = 0; i < result.shape.first; i++) {
                    newColumn.push_back(other[column][rightMap[std::get<U>(series[leftColumn][i])]]);
                }
                result.addColumn(column, Series<T>(newColumn));
            }

            return result;
        }

        template <typename U, typename V>
        DataFrame<T> groupby(std::string columnName, std::vector<std::string> columnsToAggregate, std::string aggFunction){
            /**
             * @brief Group the DataFrame by a single column and aggregate the other columns
             * 
             * @param columnName The column to group by
             * @param columnsToAggregate The columns to aggregate
             * @param aggFunction Could be "mean", "sum"
             * @return DataFrame<T> The grouped DataFrame
             */
            int columnId = column_id(columnName);

            if (columnId == -1) {
                throw std::invalid_argument("Column does not exist" + columnName);
            }
            
            std::vector<int> columnsToAggregateIds;
            for (std::string column : columnsToAggregate) {
                int aggColumnId = column_id(column);
                if (aggColumnId == -1) {
                    throw std::invalid_argument("Column does not exist" + columnName);
                }
                columnsToAggregateIds.push_back(aggColumnId);
            }

            std::map<U, std::vector<int>> groups;

            for (int i = 0; i < shape.first; i++) {
                groups[std::get<U>(series[columnId][i])].push_back(i);
            }
            
            DataFrame<T> result;

            for (auto const& [key, val] : groups) {
                if (aggFunction == "mean") {
                    int n = val.size();
                    std::vector<V> sum(columnsToAggregateIds.size(), V(0));
                    for (int i : val) {
                        for (int j = 0; j < columnsToAggregateIds.size(); j++){
                            sum[j] = sum[j] + std::get<V>(series[columnsToAggregateIds[j]][i]);
                        }
                    }
                    std::map<std::string, T> mean;
                    for (int j = 0; j < columnsToAggregateIds.size(); j++){
                        mean[columns[columnsToAggregateIds[j]]] = sum[j] / n;
                    }
                    mean[columnName] = key;
                    result.append(mean);
                } else if (aggFunction == "sum") {
                    std::vector<V> sum(columnsToAggregateIds.size(), V(0));
                    for (int i : val) {
                        for (int j = 0; j < columnsToAggregateIds.size(); j++){
                            sum[j] = sum[j] + std::get<V>(series[columnsToAggregateIds[j]][i]);
                        }
                    }
                    std::map<std::string, T> mean;
                    for (int j = 0; j < columnsToAggregateIds.size(); j++){
                        mean[columns[columnsToAggregateIds[j]]] = sum[j];
                    }
                    mean[columnName] = key;
                    result.append(mean);
                } else if (aggFunction == "max") {
                    std::vector<V> max_value(columnsToAggregateIds.size(), V(0));
                    for (int i : val) {
                        for (int j = 0; j < columnsToAggregateIds.size(); j++){
                            max_value[j] = std::max(max_value[j], std::get<V>(series[columnsToAggregateIds[j]][i]));
                        }
                    }
                    std::map<std::string, T> mean;
                    for (int j = 0; j < columnsToAggregateIds.size(); j++){
                        mean[columns[columnsToAggregateIds[j]]] = max_value[j];
                    }
                    mean[columnName] = key;
                    result.append(mean);
                } else if (aggFunction == "min") {
                    std::vector<V> min_value(columnsToAggregateIds.size(), V(100000000));
                    for (int i : val) {
                        for (int j = 0; j < columnsToAggregateIds.size(); j++){
                            min_value[j] = std::min(min_value[j], std::get<V>(series[columnsToAggregateIds[j]][i]));
                        }
                    }
                    std::map<std::string, T> mean;
                    for (int j = 0; j < columnsToAggregateIds.size(); j++){
                        mean[columns[columnsToAggregateIds[j]]] = min_value[j];
                    }
                    mean[columnName] = key;
                    result.append(mean);
                } else {
                    throw std::invalid_argument("Invalid aggregation function");
                }
            }

            return result;
        }

        template <typename U>
        DataFrame<T> count(std::string columnName, std::string columnNameCount = "count") {
            /**
             * @brief Count the number of occurrences of each value in a column
             * 
             * @param columnName The column to count
             * @return DataFrame<T> The counted DataFrame
             */
            int columnId = column_id(columnName);

            if (columnId == -1) {
                throw std::invalid_argument("Column does not exist" + columnName);
            }

            std::map<U, int> counts;

            for (int i = 0; i < shape.first; i++) {
                counts[std::get<U>(series[columnId][i])]++;
            }

            DataFrame<T> result;

            for (auto const& [key, val] : counts) {
                result.append({{columnName, key}, {columnNameCount, val}});
            }

            return result;
        }

        DataFrame<T> dropDuplicate(std::vector<std::string> subset) {
            /**
             * @brief Drop duplicate rows based on a subset of columns
             * 
             * @param subset The subset of columns to consider for duplicates
             * @return DataFrame<T> The DataFrame without duplicates
             */
            std::vector<int> columnsToConsider;
            for (std::string column : subset) {
                int columnId = column_id(column);
                if (columnId == -1) {
                    throw std::invalid_argument("Column does not exist " + column);
                }
                columnsToConsider.push_back(columnId);
            }

            std::map<std::string, int> uniqueRows;
            for (int i = 0; i < shape.first; i++) {
                std::string row;
                for (int columnId : columnsToConsider) {
                    row += std::get<std::string>(series[columnId][i]);
                }
                uniqueRows[row] = i;
            }

            DataFrame<T> result;

            for (auto const& [key, val] : uniqueRows) {
                std::map<std::string, T> row;
                for (int j = 0; j < shape.second; j++) {
                    row[columns[j]] = series[j][val];
                }
                result.append(row);
            }

            return result;

        }

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
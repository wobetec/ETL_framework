#include <fstream>   // For file input/output operations
#include <iostream>  // For basic input/output
#include <sstream>   // For string stream operations
#include <string>    // For string handling
#include <vector>    // For dynamic arrays
#include "repodata.h"
#include "dataframe.h"
#include "default_object.h"
#include "sqlite3.h"

// Constructor
RepoData::RepoData() {
    strategy_ = nullptr;
}

// Set Strategy
void RepoData::setStrategy(int type, std::string path, std::string dbAdress,
                            std::string query) {
    delete strategy_;
    switch (type) {
        case ExtractorCSVType:
            strategy_ = new ExtractorCSV(path);
            break;
        case ExtractorTXTType:
            strategy_ = new ExtractorTXT(path);
            break;
        // case ExtractorSQLType:
        //     strategy_ = new ExtractorSQL(dbAdress, query);
        //     break;
        default:
            strategy_ = nullptr;
            break;
    }
}

DataFrame<DefaultObject> RepoData::extractData() {
    DataFrame<DefaultObject> df = strategy_->extractData();
    return df;
}

void RepoData::loadData(DataFrame<DefaultObject> *df) {
    strategy_->loadData();
}

std::vector<std::vector<std::string>> ExtractorEstrategy::readTextFile(std::string sep) {
    std::fstream file;

    file.open(path_, std::ios::in);
    if (!file.is_open()) {
         std::cerr << "Error opening file" << std::endl;
         return std::vector<std::vector<std::string>>();
    }

    std::string line;
    std::vector<std::vector<std::string>> allData = {};

    while (std::getline(file, line, '\n')) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> data;
        while (std::getline(ss, cell, sep[0])) {
            data.push_back(cell);
        }
        allData.push_back(data);
    }
    return allData;
}

// ExtractorCSV
DataFrame<DefaultObject> ExtractorCSV::extractData() {
    std::cout << "Extracting data from CSV file" << std::endl;
    std::vector<std::vector<std::string>> data = readTextFile(",");
    return DataFrame<DefaultObject>();
}

void ExtractorCSV::loadData() {
    std::cout << "Loading data from CSV file" << std::endl;
}


// ExtractorTXT
DataFrame<DefaultObject> ExtractorTXT::extractData() {
    std::cout << "Extracting data from TXT file" << std::endl;
    std::vector<std::vector<std::string>> data = readTextFile(" ");
    return DataFrame<DefaultObject>();
}

void ExtractorTXT::loadData() {
    std::cout << "Loading data from TXT file" << std::endl;
}


// ExtractorSQL
// DataFrame<DefaultObject> ExtractorSQL::extractData() {
//     std::cout << "Extracting data from SQL database" << std::endl;
//     doQuery(query_);
//     return DataFrame<DefaultObject>();
// }

// void ExtractorSQL::loadData() {
//     std::cout << "Loading data from SQL database" << std::endl;
//     doQuery(query_);
// }

// void ExtractorSQL::doQuery(std::string query) {
//     sqlite3_stmt* stmt;
//     exit_ = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
//     if (exit_ != SQLITE_OK) {
//         std::cerr << "Error preparing statement" << std::endl;
//         return;
//     }

//     while ((exit_ = sqlite3_step(stmt)) == SQLITE_ROW) {
//         std::cout << sqlite3_column_text(stmt, 0) << std::endl;
//     }

//     sqlite3_finalize(stmt);
// }
#include <fstream>   // For file input/output operations
#include <iostream>  // For basic input/output
#include <sstream>   // For string stream operations
#include <string>    // For string handling
#include <vector>    // For dynamic arrays
#include "repodata.h"
#include "dataframe.h"
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
        case ExtractorSQLType:
            strategy_ = new ExtractorSQL(dbAdress, query);
            break;
        default:
            strategy_ = nullptr;
            break;
    }
}

void RepoData::extractData() {
    strategy_->extractData();
}

void RepoData::loadData() {
    strategy_->loadData();
}

// ExtractorCSV
void ExtractorCSV::extractData() {
    std::cout << "Extracting data from CSV file" << std::endl;
    readCSV();
}

void ExtractorCSV::loadData() {
    std::cout << "Loading data from CSV file" << std::endl;
}

void ExtractorCSV::readCSV() {
    std::fstream file;

    file.open(path_, std::ios::in);
    if (!file.is_open()) {
         std::cerr << "Error opening file" << std::endl;
         return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        // std::cout << row[0] << std::endl;
    }
}

// ExtractorTXT
void ExtractorTXT::extractData() {
    std::cout << "Extracting data from TXT file" << std::endl;
    readTXT();
}

void ExtractorTXT::loadData() {
    std::cout << "Loading data from TXT file" << std::endl;
}

void ExtractorTXT::readTXT() {
    std::fstream file;

    file.open(path_, std::ios::in);
    if (!file.is_open()) {
         std::cerr << "Error opening file" << std::endl;
         return;
    }

    std::string line;
    while (std::getline(file, line, '\n')) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> data;
        while (std::getline(ss, cell, ' ')) {
            data.push_back(cell);
        }
        // std::cout << data[0] << std::endl;
    }
}

// ExtractorSQL
void ExtractorSQL::extractData() {
    std::cout << "Extracting data from SQL database" << std::endl;
    doQuery(query_);
}

void ExtractorSQL::loadData() {
    std::cout << "Loading data from SQL database" << std::endl;
    doQuery(query_);
}

void ExtractorSQL::doQuery(std::string query) {
    sqlite3_stmt* stmt;
    exit_ = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
    if (exit_ != SQLITE_OK) {
        std::cerr << "Error preparing statement" << std::endl;
        return;
    }

    while ((exit_ = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << sqlite3_column_text(stmt, 0) << std::endl;
    }

    sqlite3_finalize(stmt);
}
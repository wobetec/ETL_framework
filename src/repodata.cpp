#include <fstream>   // For file input/output operations
#include <iostream>  // For basic input/output
#include <sstream>   // For string stream operations
#include <string>    // For string handling
#include <vector>    // For dynamic arrays
#include "repodata.h"

// Constructor
RepoData::RepoData() {
    strategy_ = nullptr;
}

// Set Strategy
void RepoData::setStrategy(int type, std::string path, std::string dbAdress,
                            std::string query, int* pointer, int size) {
    delete strategy_;
    switch (type) {
        case ExtractorCSVType:
            strategy_ = new ExtractorCSV(path);
            break;
        case ExtractorTXTType:
            strategy_ = new ExtractorTXT(path);
            break;
        case ExtractorMemoryType:
            strategy_ = new ExtractorMemory(pointer, size);
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
    std::fstream fin; 
  
    // Open an existing file 
    fin.open(path_, std::ios::in);

    // Read the Data from the file
    std::string line, word;
    std::vector<std::string> row;

    while (fin >> word) {
        row.clear();

        getline(fin, line);

        std::stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        // print the data of the row
        for (std::string data : row) {
            std::cout << data << "\t";
        }
    }
}

// ExtractorTXT
void ExtractorTXT::extractData() {
    std::cout << "Extracting data from TXT file" << std::endl;
}

void ExtractorTXT::loadData() {
    std::cout << "Loading data from TXT file" << std::endl;
}

// ExtractorMemory
void ExtractorMemory::extractData() {
    std::cout << "Extracting data from memory" << std::endl;
}

void ExtractorMemory::loadData() {
    std::cout << "Loading data from memory" << std::endl;
}

// ExtractorSQL
void ExtractorSQL::extractData() {
    std::cout << "Extracting data from SQL database" << std::endl;
}

void ExtractorSQL::loadData() {
    std::cout << "Loading data from SQL database" << std::endl;
}
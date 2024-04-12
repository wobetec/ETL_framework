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
            strategy_ = new ExtractorCSV();
            break;
        case ExtractorTXTType:
            strategy_ = new ExtractorTXT();
            break;
        case ExtractorMemoryType:
            strategy_ = new ExtractorMemory();
            break;
        case ExtractorSQLType:
            strategy_ = new ExtractorSQL();
            break;
        default:
            strategy_ = nullptr;
            break;
    }
}

// Extract Data
void RepoData::extractData() {
    strategy_->extractData();
}

// Load Data
void RepoData::loadData() {
    strategy_->loadData();
}

void ExtractorCSV::extractData() {
    std::cout << "Extracting data from CSV file" << std::endl;
}

void ExtractorCSV::loadData() {
    std::cout << "Loading data from CSV file" << std::endl;
}

void ExtractorTXT::extractData() {
    std::cout << "Extracting data from TXT file" << std::endl;
}

void ExtractorTXT::loadData() {
    std::cout << "Loading data from TXT file" << std::endl;
}

void ExtractorMemory::extractData() {
    std::cout << "Extracting data from memory" << std::endl;
}

void ExtractorMemory::loadData() {
    std::cout << "Loading data from memory" << std::endl;
}

void ExtractorSQL::extractData() {
    std::cout << "Extracting data from SQL database" << std::endl;
}

void ExtractorSQL::loadData() {
    std::cout << "Loading data from SQL database" << std::endl;
}
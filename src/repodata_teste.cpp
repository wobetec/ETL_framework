#include "repodata.h"

int main() {
    // Create an instance of RepoData
    RepoData repo;
    
    // Set the strategy to ExtractorCSV
    repo.setStrategy(RepoData::ExtractorCSVType, "test.csv");
    repo.extractData();
    repo.loadData();
    
    // Set the strategy to ExtractorTXT
    repo.setStrategy(RepoData::ExtractorTXTType);
    repo.extractData();
    repo.loadData();

    // Set the strategy to ExtractorMemory
    repo.setStrategy(RepoData::ExtractorMemoryType);
    repo.extractData();
    repo.loadData();

    // Set the strategy to ExtractorSQL
    repo.setStrategy(RepoData::ExtractorSQLType);
    repo.extractData();
    repo.loadData();
    
    return 0;
}

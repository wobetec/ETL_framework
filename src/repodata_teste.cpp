#include "repodata.h"

int main() {
    RepoData repoData;
    repoData.setStrategy(RepoData::ExtractorTXTType, "teste.txt", "", "");
    repoData.extractData();

    return 0;
}
#include "repodata.h"

int main() {
    RepoData repoData;
    repoData.setStrategy(RepoData::ExtractorTXTType, "teste.txt", "", "", nullptr, 0);
    repoData.extractData();

    return 0;
}
#include "repodata.h"
#include "dataframe.h"

int main() {
    RepoData repoData;
    repoData.setStrategy(RepoData::ExtractorCSVType, "teste.csv", "", "");
    DataFrame<DefaultObject> df = repoData.extractData();

    for (auto column : df.columns) {
        for (auto value : column) {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    df.print();
    return 0;
}
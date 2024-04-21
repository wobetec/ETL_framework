#include "repodata.h"
#include "dataframe.h"

using namespace std;

int main() {
    RepoData repoData;
    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/products.txt", "", "");
    DataFrame<DefaultObject> df = repoData.extractData();

    df.print();

    for(string s : df.columns){
        cout << s << endl;
    }

    cout << df.shape.first << " " << df.shape.second << endl;
    // df["notification_date"].print();
    return 0;
}
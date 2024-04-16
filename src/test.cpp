#include "framework.h"

using namespace std;

int main() {

    DataFrame<DefaultObject> df;
    df.addColumn("column1", Series<DefaultObject>({"a", "b", "c"}));
    df.addColumn("column2", Series<DefaultObject>({1, 2, 3}));
    df.print();

    df.addColumn("column3", df["column2"].sub<int>(df["column2"]));
    df.addColumn("column4", df["column1"].add<string>(df["column1"]));
    df.addColumn("column5", df["column2"].sub<int>(2));

    df["column3"].print();

    df.print();

    df.dropSeries("column3");

    df.print();

    return 0;
}

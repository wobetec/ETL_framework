#include "../src/framework.h"
#include <bits/stdc++.h>

using namespace std;

void TestSeries(){

    cout << "//####################################################################" << endl;
    cout << "// Series" << endl;
    cout << "//####################################################################" << endl;

    //####################################################################
    // Constructor
    //####################################################################
    cout << "Series()" << endl;
    Series<DefaultObject> s;

    assert(s.shape() == 0);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // Constructor
    //####################################################################
    cout << "Series(vector<DefaultObject>)" << endl;
    Series<DefaultObject> s1({1, 2, 3, 4, 5});

    assert(s1.shape() == 5);
    cout << ".";

    assert(get<int>(s1[0]) == 1);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // append
    //####################################################################
    cout << "append(DefaultObject)" << endl;
    s1.append(6);

    assert(s1.shape() == 6);
    cout << ".";

    assert(get<int>(s1[5]) == 6);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // append
    //####################################################################
    cout << "append(Series)" << endl;
    Series<DefaultObject> s2({7, 8, 9, 10});
    Series<DefaultObject> s3 = s1.append(s2);

    assert(s3.shape() == 10);
    cout << ".";

    assert(get<int>(s3[9]) == 10);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // operator[]
    //####################################################################
    cout << "operator[]" << endl;
    
    assert(get<int>(s3[0]) == 1);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // add
    //####################################################################
    cout << "add(Series)" << endl;
    Series<DefaultObject> s4 = s3.add<int>(s3);

    assert(s4.shape() == 10);
    cout << ".";

    assert(get<int>(s4[9]) == 20);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // add
    //####################################################################
    cout << "add(DefaultObject)" << endl;
    Series<DefaultObject> s5 = s4.add<int>(5);

    assert(s5.shape() == 10);
    cout << ".";

    assert(get<int>(s5[9]) == 25);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // copy
    //####################################################################
    cout << "copy()" << endl;
    Series<DefaultObject> s6 = s5.copy();

    assert(s6.shape() == 10);
    cout << ".";

    assert(get<int>(s6[9]) == 25);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // compare
    //####################################################################
    cout << "compare(value, string)" << endl;
    Series<DefaultObject> s7 = s6.compare<int>(25, "==");

    assert(s7.shape() == 10);
    cout << ".";

    assert(get<bool>(s7[1]) == false);
    cout << ".";

    assert(get<bool>(s7[9]) == true);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // astype
    //####################################################################
    cout << "astype<string, int>()" << endl;
    Series<DefaultObject> s8({"1", "2", "3", "4", "5"});
    Series<DefaultObject> s9 = s8.astype<string, int>();

    assert(s9.shape() == 5);
    cout << ".";

    assert(get<int>(s9[0]) == 1);
    cout << ".";

    cout << " OK" << endl;
    
    cout << "//############################>>> DONE <<<############################" << endl << endl;
}

void TestDataFrame(){

    cout << "//####################################################################" << endl;
    cout << "// DataFrame" << endl;
    cout << "//####################################################################" << endl;

    //####################################################################
    // Constructor
    //####################################################################
    cout << "DataFrame()" << endl;
    DataFrame<DefaultObject> df;

    assert(df.shape.first == 0);
    cout << ".";

    assert(df.shape.second == 0);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // AddColumn
    //####################################################################
    cout << "addColumn(string, vector<DefaultObject>)" << endl;
    Series<DefaultObject> s1({1, 2, 3, 4, 5});
    df.addColumn("col1", s1);

    assert(df.shape.first == s1.shape());
    cout << ".";

    assert(df.shape.second == 1);
    cout << ".";

    assert(df.columns[0] == "col1");
    cout << ".";

    Series<DefaultObject> s2({6, 7, 8, 9, 10});
    df.addColumn("col2", s2);

    assert(df.shape.first == s1.shape());
    cout << ".";

    assert(df.shape.second == 2);
    cout << ".";

    assert(df.columns[1] == "col2");
    cout << ".";

    df.addColumn("col1", s2);

    assert(df.shape.first == s1.shape());
    cout << ".";

    assert(df.shape.second == 2);
    cout << ".";

    assert(df.columns[0] == "col1");
    cout << ".";

    assert(get<int>(df.series[0][0]) == get<int>(s2[0]));
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // renameColumn
    //####################################################################
    cout << "renameColumn(string, string)" << endl;
    df.renameColumn("col1", "col3");

    assert(df.columns[0] == "col3");
    cout << ".";

    df.renameColumn("col3", "col1");
    assert(df.columns[0] == "col1");
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // Constructor
    //####################################################################
    cout << "DataFrame(vector<string>, vector<Series>)" << endl;
    DataFrame<DefaultObject> df2({"col1", "col2"}, {s1, s2});

    assert(df2.shape.first == s1.shape());
    cout << ".";

    assert(df2.shape.second == 2);
    cout << ".";

    assert(df2.columns[0] == "col1");
    cout << ".";

    assert(get<int>(df2.series[0][0]) == get<int>(s1[0]));
    cout << ".";

    cout << " OK" << endl;

    //####################################################################'
    // DataFrame
    //####################################################################
    cout << "DataFrame(map<string, Series>)" << endl;
    DataFrame<DefaultObject> df3({{"col1", s1}, {"col2", s2}});

    assert(df3.shape.first == s1.shape());
    cout << ".";

    assert(df3.shape.second == 2);
    cout << ".";

    assert(df3.columns[0] == "col1");
    cout << ".";

    assert(get<int>(df3.series[0][0]) == get<int>(s1[0]));
    cout << ".";

    cout << " OK" << endl;

    //####################################################################'
    // copy
    //####################################################################
    cout << "copy()" << endl;
    DataFrame<DefaultObject> df4 = df3.copy();

    assert(df4.shape.first == s1.shape());
    cout << ".";

    assert(df4.shape.second == 2);
    cout << ".";

    assert(df4.columns[0] == "col1");
    cout << ".";

    assert(get<int>(df4.series[0][0]) == get<int>(s1[0]));
    cout << ".";

    cout << " OK" << endl;

    //####################################################################'
    // append
    //####################################################################
    cout << "append()" << endl;
    df3.append({{"col1", 0}, {"col2", 9}});

    assert(df3.shape.first == s1.shape() + 1);
    cout << ".";

    assert(df3.shape.second == 2);
    cout << ".";

    assert(df3.columns[0] == "col1");
    cout << ".";

    assert(get<int>(df3.series[0][6]) == 0);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // operator[string]
    //####################################################################
    cout << "operator[string]" << endl;
    Series<DefaultObject> s3 = df3["col1"];

    assert(s3.shape() == s1.shape() + 1);
    cout << ".";

    assert(get<int>(s3[6]) == 0);
    cout << ".";
    
    cout << " OK" << endl;

    // ####################################################################
    // operator[vector<string>]
    // ####################################################################
    cout << "operator[vector<string>]" << endl;
    df3.addColumn("col3", Series<DefaultObject>({11, 21, 31, 41, 51, 6}));
    DataFrame<DefaultObject> df5 = df3[vector<string>{"col2", "col1"}];

    assert(df5.shape.first == s1.shape() + 1);
    cout << ".";

    assert(df5.shape.second == 2);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // dropColumn
    //####################################################################
    cout << "dropColumn(string)" << endl;
    df3.dropColumn("col1");

    assert(df3.shape.first == s1.shape() + 1);
    cout << ".";

    assert(df3.shape.second == 2);
    cout << ".";

    assert(df3.columns[0] == "col2");
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // concat
    //####################################################################
    cout << "concat(&DataFrame)" << endl;
    DataFrame<DefaultObject> df6 = df.concat(df5);

    assert(df6.shape.first == df5.shape.first + df.shape.first);
    cout << ".";

    assert(df6.shape.second == df.shape.second);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // filter
    //####################################################################
    cout << "filter(Series)" << endl;
    Series<DefaultObject> s4 = df6["col2"].compare<int>(9, "==");
    DataFrame<DefaultObject> df7 = df6.filter(s4);

    assert(df7.shape.first == 3);
    cout << ".";

    assert(df7.shape.second == 2);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // filter
    //####################################################################
    cout << "filter(string, string, U)" << endl;
    DataFrame<DefaultObject> df8 = df6.filter("col2", "==", 9);

    assert(df8.shape.first == 3);
    cout << ".";

    assert(df8.shape.second == 2);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // sort
    //####################################################################
    cout << "sort(string)" << endl;
    DataFrame<DefaultObject> df9 = df6.sort<int>("col1");

    assert(get<int>(df9["col1"][0]) == 0);
    cout << ".";

    assert(get<int>(df9["col1"][1]) == 1);
    cout << ".";

    assert(get<int>(df9["col1"][10]) == 10);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // merge
    //####################################################################
    cout << "merge(&DataFrame, string, string)" << endl;
    DataFrame<DefaultObject> df10({"col3", "col1"}, {Series<DefaultObject>({"v", "a", "c", "d", "e"}), Series<DefaultObject>({5, 2, 1, 4, 3})});
    DataFrame<DefaultObject> df11 = df5.merge<int>(df10, "col1", "col1");

    assert(df11.shape.first == 5);
    cout << ".";

    assert(df11.shape.second == 3);
    cout << ".";

    assert(df11.columns[2] == "col3");
    cout << ".";

    assert(get<string>(df11["col3"][0]) == "c");
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // gorupby
    //####################################################################
    cout << "groupby<U, V>(string, vector<string>, string)" << endl;
    df = DataFrame<DefaultObject>({{"col1", Series<DefaultObject>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})}, {"col2", Series<DefaultObject>({2, 2, 2, 3, 3, 3, 4, 4, 4, 5})}});
    DataFrame<DefaultObject> df1 = df.groupby<int, int>("col2", {"col1"}, "sum");

    assert(df1.shape.first == 4);
    cout << ".";

    assert(df1.shape.second == 2);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // count
    //####################################################################
    cout << "count(string)" << endl;
    df1 = df.count<int>("col2");

    assert(get<int>(df1["count"][0]) == 3);
    cout << ".";

    cout << " OK" << endl;

    //####################################################################
    // dropDuplicate
    //####################################################################
    cout << "dropDuplicate(vector<string>)" << endl;
    df = DataFrame<DefaultObject>({{"col1", Series<DefaultObject>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})}, {"col2", Series<DefaultObject>({"a", "a", "b", "b", "c", "c", "d", "d", "e", "e"})}});
    df1 = df.dropDuplicate(vector<string>{"col2"});

    assert(df1.shape.first == 5);
    cout << ".";

    assert(df1.shape.second == 2);
    cout << ".";

    cout << " OK" << endl;

    cout << "//############################>>> DONE <<<############################" << endl << endl;
}

int main(){

    TestSeries();

    TestDataFrame();


    return 0;
}
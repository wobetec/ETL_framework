#include "./src/DF.h"

using namespace std;

int main(){

    DF_CadeAnalytics df;
    df.append({1, "estimulo", "componente alvo", DateTime(2021, 1, 1)});
    df.append({2, "estimulo", "componente alvo", DateTime(2021, 1, 2)});
    df.print();

    return 0;
}
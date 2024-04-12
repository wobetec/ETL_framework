#include "./src/DF.h"

using namespace std;

int main(){

    DF_CadeAnalytics df;
    df.append({DateTime(), 1, "Estimulo 1", "Componente 1"});
    df.append({DateTime(), 2, "Estimulo 2", "Componente 2"});
    df.print();

    return 0;
}
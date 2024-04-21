#include "repodata.h"
#include "dataframe.h"
#include "db.h"
#include "sqlite3.h"
#include "series.h"

int main() {
    RepoData repoData;
    repoData.setStrategy(RepoData::ExtractorCSVType, "teste.csv");
    DataFrame<DefaultObject> df = repoData.extractData();

    for (auto column : df.columns) {
        for (auto value : column) {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    df.print();


    DB db("new.db");
    sqlite3_stmt *stmt;
    const char *sql;
    sql = "SELECT * FROM T1;";
    sqlite3_prepare_v2(db.db, sql, -1, &stmt, NULL);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << sqlite3_column_text(stmt, 0) << " " << sqlite3_column_double(stmt, 1) << std::endl;
    }

    //destry db
    sqlite3_finalize(stmt);
    df.addColumn("count", df["count"].astype<std::string, int>());

    RepoData loader;
    loader.setStrategy(RepoData::ExtractorSQLType, "", &db, "T1");
    loader.loadData(&df);

    db.insertData("T1", "2020-01-01 00:00:01", 20.0);
    db.insertData("T1", "2020-01-01 00:00:02", 30.0);

    // print all t1
   
    return 0;
}
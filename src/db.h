#ifndef DB_H
#define DB_H


#include <fstream>   // For file input/output operations
#include <iostream>  // For basic input/output
#include <sstream>   // For string stream operations
#include <string>    // For string handling
#include <vector>    // For dynamic arrays
#include <cstring>
// #include "repodata.h"
// #include "dataframe.h"
#include "sqlite3.h"
// #include "series.h"

class DB {
    public:
        sqlite3 *db;
        DB(const std::string db_name){
            sqlite3_open(db_name.c_str(), &db);
            char *errMsg = 0;
            const char *sql;

            // Create tables for our solution with datetime primary key and count integer
            sql = "CREATE TABLE IF NOT EXISTS T1 (datetime TEXT PRIMARY KEY, count FLOAT);";   
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
            sql = "CREATE TABLE IF NOT EXISTS T5 (nomeproduto TEXT PRIMARY KEY, count FLOAT);"; 
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
            sql = "CREATE TABLE IF NOT EXISTS T3 (datetime TEXT PRIMARY KEY, count FLOAT);";
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
            sql = "CREATE TABLE IF NOT EXISTS T6 (datetime TEXT PRIMARY KEY, mean FLOAT);";
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
            sql = "CREATE TABLE IF NOT EXISTS T2 (datetime TEXT PRIMARY KEY, count FLOAT);";
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
            sql = "CREATE TABLE IF NOT EXISTS T4 (nomeproduto TEXT PRIMARY KEY, count FLOAT);";
            sqlite3_exec(db, sql, NULL, 0, &errMsg);
        }
        ~DB(){
            sqlite3_close(db);
        }

        void insertData(std::string table, std::string column1, float column2){
            std::string sql = "BEGIN TRANSACTION; INSERT OR REPLACE INTO " + table + " (datetime, count) VALUES ('" + column1 + "', " + std::to_string(column2) + "); COMMIT;";
            char *errMsg = 0;
            sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        }
};

// int main(){
//     DB db("test.db");
//     db.insertData("T1", "2020-01-01 00:00:00", 1.0);
//     db.insertData("T2", "2020-01-01 00:00:01", 2.0);
//     db.insertData("T3", "2020-01-01 00:00:02", 3.0);
//     db.insertData("T4", "2020-01-01 00:00:03", 4.0);
//     db.insertData("T5", "2020-01-01 00:00:04", 5.0);
//     db.insertData("T6", "2020-01-01 00:00:05", 6.0);
//     db.insertData("T1", "2020-01-01 00:00:06", 7.0);
//     db.insertData("T2", "2020-01-01 00:00:07", 8.0);
//     db.insertData("T3", "2020-01-01 00:00:08", 9.0);
//     db.insertData("T4", "2020-01-01 00:00:09", 10.0);
//     db.insertData("T5", "2020-01-01 00:00:10", 11.0);
//     db.insertData("T6", "2020-01-01 00:00:11", 12.0);

//     // print the tables
//     sqlite3_stmt *stmt;
//     const char *sql;
//     sql = "SELECT * FROM T1;";
//     sqlite3_prepare_v2(db.db, sql, -1, &stmt, NULL);
//     while (sqlite3_step(stmt) == SQLITE_ROW) {
//         std::cout << sqlite3_column_text(stmt, 0) << " " << sqlite3_column_double(stmt, 1) << std::endl;
//     }
//     sqlite3_finalize(stmt);
// }

#endif
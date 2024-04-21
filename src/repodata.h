#ifndef REPDATA_H
#define REPDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "dataframe.h"
#include "sqlite3.h"
#include "default_object.h"

// Forward declaration of ExtractorEstrategy
class ExtractorEstrategy;

class RepoData {
public:
    enum ExtractorEstrategyType {
        ExtractorCSVType,
        ExtractorTXTType,
        // ExtractorSQLType
    };
    RepoData();
    void setStrategy(int type, std::string path = "", std::string dbAdress = "",
                     std::string query = "");
    DataFrame<DefaultObject> extractData();
    void loadData(DataFrame<DefaultObject> *df);
    ExtractorEstrategy* strategy_ = nullptr;

private:
};

class ExtractorEstrategy {
public:
    std::string path_;
    std::string dbAdress_;
    std::string query_;
    int* pointer_;
    int size_;
    virtual DataFrame<DefaultObject> extractData() = 0;
    virtual void loadData() = 0;
    std::vector<std::vector<std::string>> readTextFile(std::string sep);
};

class ExtractorCSV : public ExtractorEstrategy {
public:
    ExtractorCSV(std::string path){
        path_ = path;
    };
    DataFrame<DefaultObject> extractData() override;
    void loadData() override;
};

class ExtractorTXT : public ExtractorEstrategy {
public:
    ExtractorTXT(std::string path){
        path_ = path;
    };
    DataFrame<DefaultObject> extractData() override;
    void loadData() override;
};

// class ExtractorSQL : public ExtractorEstrategy {
// public:
//     sqlite3* db_;
//     int exit_ = 0;
//     ExtractorSQL(std::string dbAdress, std::string query){
//         dbAdress_ = dbAdress;
//         exit_ = sqlite3_open(dbAdress.c_str(), &db_);
//         query_ = query;
//     };
//     DataFrame<DefaultObject> extractData() override;
//     void loadData() override;
//     void doQuery(std::string query);
// };

#endif // REPDATA_H
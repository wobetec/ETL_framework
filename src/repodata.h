#ifndef REPDATA_H
#define REPDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "dataframe.h"
#include "sqlite3.h"

// Forward declaration of ExtractorEstrategy
class ExtractorEstrategy;

class RepoData {
public:
    enum ExtractorEstrategyType {
        ExtractorCSVType,
        ExtractorTXTType,
        ExtractorSQLType
    };
    RepoData();
    void setStrategy(int type, std::string path = "", std::string dbAdress = "",
                     std::string query = "");
    void extractData();
    void loadData();
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
    virtual void extractData() = 0;
    virtual void loadData() = 0;
    void readTextFile(std::string sep);
};

class ExtractorCSV : public ExtractorEstrategy {
public:
    ExtractorCSV(std::string path){
        path_ = path;
    };
    void extractData() override;
    void loadData() override;
};

class ExtractorTXT : public ExtractorEstrategy {
public:
    ExtractorTXT(std::string path){
        path_ = path;
    };
    void extractData() override;
    void loadData() override;
};

class ExtractorSQL : public ExtractorEstrategy {
public:
    sqlite3* db_;
    int exit_ = 0;
    ExtractorSQL(std::string dbAdress, std::string query){
        dbAdress_ = dbAdress;
        // exit_ = sqlite3_open(dbAdress.c_str(), &db_);
        query_ = query;
    };
    void extractData() override;
    void loadData() override;
    void doQuery(std::string query);
};

#endif // REPDATA_H
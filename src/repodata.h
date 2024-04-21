#ifndef REPDATA_H
#define REPDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "dataframe.h"
#include "sqlite3.h"
#include "default_object.h"
#include "series.h"
#include "db.h"

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
    void setStrategy(int type, std::string path = "", DB *db = nullptr, std::string table = "");
    DataFrame<DefaultObject> extractData();
    void loadData(DataFrame<DefaultObject> *df);
    ExtractorEstrategy* strategy_ = nullptr;

private:
};

class ExtractorEstrategy {
public:
    std::string path_;
    DB* db_;
    std::string table_;
    int* pointer_;
    int size_;
    virtual DataFrame<DefaultObject> extractData() = 0;
    virtual void loadData(DataFrame<DefaultObject> *df) = 0;
    std::vector<std::vector<std::string>> readTextFile(std::string sep);
    void saveTextFile(DataFrame<DefaultObject> *df, std::string sep);
};

class ExtractorCSV : public ExtractorEstrategy {
public:
    ExtractorCSV(std::string path){
        path_ = path;
    };
    DataFrame<DefaultObject> extractData() override;
    void loadData(DataFrame<DefaultObject> *df) override;
};

class ExtractorTXT : public ExtractorEstrategy {
public:
    ExtractorTXT(std::string path){
        path_ = path;
    };
    DataFrame<DefaultObject> extractData() override;
    void loadData(DataFrame<DefaultObject> *df) override;
};

class ExtractorSQL : public ExtractorEstrategy {
public:
    int exit_ = 0;
    ExtractorSQL(DB *db, std::string table = ""){
        db_ = db;
        table_ = table;
    };
    DataFrame<DefaultObject> extractData() override;
    void loadData(DataFrame<DefaultObject> *df) override;
};

#endif // REPDATA_H
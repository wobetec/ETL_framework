#ifndef REPDATA_H
#define REPDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Forward declaration of ExtractorEstrategy
class ExtractorEstrategy;

class RepoData {
public:
    enum ExtractorEstrategyType {
        ExtractorCSVType,
        ExtractorTXTType,
        ExtractorMemoryType,
        ExtractorSQLType
    };
    RepoData();
    void setStrategy(int type, std::string path = "", std::string dbAdress = "",
                     std::string query = "", int* pointer = nullptr, int size = 0);
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
};

class ExtractorCSV : public ExtractorEstrategy {
public:
    ExtractorCSV(std::string path){
        path_ = path;
    };
    void extractData() override;
    void loadData() override;
    void readCSV();
};

class ExtractorTXT : public ExtractorEstrategy {
public:
    ExtractorTXT(std::string path){
        path_ = path;
    };
    void extractData() override;
    void loadData() override;
};

class ExtractorMemory : public ExtractorEstrategy {
public:
    ExtractorMemory(int* pointer, int size){
        pointer_ = pointer;
        size_ = size;
    };
    void extractData() override;
    void loadData() override;
};

class ExtractorSQL : public ExtractorEstrategy {
public:
    ExtractorSQL(std::string dbAdress, std::string query){
        dbAdress_ = dbAdress;
        query_ = query;
    };
    void extractData() override;
    void loadData() override;
};

#endif // REPDATA_H
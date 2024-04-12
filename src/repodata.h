#ifndef REPDATA_H
#define REPDATA_H

#include <iostream>
#include <string>
#include <vector>

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

private:
    ExtractorEstrategy* strategy_ = nullptr;
};

class ExtractorEstrategy {
public:
    virtual void extractData() = 0;
    virtual void loadData() = 0;
};

class ExtractorCSV : public ExtractorEstrategy {
public:
    ExtractorCSV(){};
    void extractData() override;
    void loadData() override;
};

class ExtractorTXT : public ExtractorEstrategy {
public:
    ExtractorTXT(){};
    void extractData() override;
    void loadData() override;
};

class ExtractorMemory : public ExtractorEstrategy {
public:
    ExtractorMemory(){};
    void extractData() override;
    void loadData() override;
};

class ExtractorSQL : public ExtractorEstrategy {
public:
    ExtractorSQL(){};
    void extractData() override;
    void loadData() override;
};

#endif // REPDATA_H
#include <iostream>
#include <string>
#include <vector>

class RepoData {
    public:
        enum ExtractorEstrategyType {
            ExtractorCSV,
            ExtractorTXT,
            ExtractorMemory,
            ExtractorSQL
        }
        RepoData(){
            strategy_ = NULL;
        }
        void setStrategy(int type, std::string path = "", std::string dbAdress = "", 
                         std::string query = "", std::int *pointer = NULL, std::int size = 0);
        void extractData();
        void loadData();

    private:
        ExtractorEstrategy* strategy_;
};


class ExtractorEstrategy {
    public:
        virtual void extractData() = 0;
        virtual void loadData() = 0;        
};


class ExtractorCSV : public ExtractorEstrategy {
    public:
        ExtractorCSV(std::string path);
        void extractData();
        void loadData();
};


class ExtractorTXT : public ExtractorEstrategy {
    public:
        ExtractorTXT(std::string path);
        void extractData();
        void loadData();
};


class ExtractorMemory : public ExtractorEstrategy {
    public:
        ExtractorMemory(std::int *pointer, std::int size);
        void extractData();
        void loadData();
};


class ExtractorSQL : public ExtractorEstrategy {
    public:
        ExtractorSQL(std::string dbAdress, std::string query);
        void extractData();
        void loadData();
};
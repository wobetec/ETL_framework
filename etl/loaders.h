#include "../src/framework.h"
#include "object.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "../src/db.h"
#include <chrono>
#include <fstream>   // For file input/output operations
#include <sstream>   // For string stream operations

class LoaderThreads : public ThreadWrapper<Queue<std::string, DataFrame<Object>>, Queue<std::string, DataFrame<Object>>> {
    public:
        LoaderThreads(
            Queue<std::string, DataFrame<Object>> &inQueue
        ) : ThreadWrapper(inQueue, outQueues) {}

        void run() override {
            DB db("new.db");
            while (running) {
                std::cout << "Loading data to SQLite" << std::endl;

                RepoData loader;

                std::pair<std::string, DataFrame<Object>> data = inQueue.deQueue();
                
                std::string key = data.first;
                size_t spacePos = key.find(' ');
                std::string key_name = key.substr(0, spacePos);
                std::string key_time = key.substr(spacePos + 1);

                DataFrame<Object> df = data.second;

                loader.setStrategy(RepoData::ExtractorSQLType, "", &db, key);
                loader.loadData(&df);

                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::ofstream file;
                file.open("times.txt", std::ios::out);
                file << key_name << " " << key_time << " " << std::ctime(&now);
                file.close();
            }
        }
};
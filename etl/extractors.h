#include "../src/framework.h"
#include "object.h"
#include <iostream>
#include <string>
#include <filesystem>


class ExtractThread : public ThreadWrapper<Queue<std::string, std::string>, Queue<std::string, DataFrame<Object>>> {
    public:
        ExtractThread(
            Queue<std::string, std::string> &inQueue,
            Queue<std::string, DataFrame<Object>> &outQueues,
            MapMutex<std::string> &map_mutex
        ) : ThreadWrapper(inQueue, outQueues), map_mutex(map_mutex) {}

        void run() override {
            RepoData repoData;
            while (running) {
                std::cout << "Extracting data" << std::endl;

                std::pair<std::string, std::string> data = inQueue.deQueue();

                std::string key = data.first;
                std::string value = data.second;
                DataFrame<Object> df;

                if (key == "produtos") {
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/products.txt");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "estoque") {
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/stock.txt");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "compras") {
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/orders.txt");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "cade"){
                    std::cout << "#######> cade" << std::endl;
                    std::cout << "HHHHHHHHHH " << value << std::endl;
                    repoData.setStrategy(RepoData::ExtractorStringType, value);
                    df = repoData.extractData();
                    std::cout << "#######> cade" << std::endl;
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "datacat") {
                    auto lock = map_mutex.getLock("datacat");

                    std::string last_path = map_mutex.get("datacat_behavior");
                    std::string max_path = last_path;
                    std::string base_path = "../simulator/data/datacat/behavior/";
                    for (const auto & entry : std::filesystem::directory_iterator(base_path)) {
                        std::string filename = std::string(entry.path().string());

                        if (filename > last_path){
                            repoData.setStrategy(RepoData::ExtractorTXTType, filename);
                            df = repoData.extractData();

                            if (df.shape.first > 0) {
                                outQueues.enQueue(std::make_pair(key, df));
                            }

                            if ( filename > max_path ) {
                                max_path = filename;
                            }
                        }
                    }

                    map_mutex.set("datacat_behavior", max_path);
                    lock.unlock();
                }
            }
        }

        MapMutex<std::string> &map_mutex;
};
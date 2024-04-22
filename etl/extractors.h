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
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/products.txt", "", "");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "estoque") {
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/stock.txt", "", "");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "compras") {
                    repoData.setStrategy(RepoData::ExtractorCSVType, "../simulator/data/contaverde/purchase_orders.txt", "", "");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "cade"){
                    repoData.setStrategy(RepoData::ExtractorTXTType, "../simulator/data/cadeanalytics/cade_analytics.txt", "", "");
                    df = repoData.extractData();
                    outQueues.enQueue(std::make_pair(key, df));
                } else if (key == "datacat") {
                    auto lock = map_mutex.getLock("datacat");

                    std::string last_path = map_mutex.get("datacat_behaviour");
                    std::string max_path = last_path;
                    std::string base_path = "../simulator/data/datacat/behaviour/";
                    for (const auto & entry : std::filesystem::directory_iterator(base_path)) {
                        std::string filename = std::string(entry.path());

                        if (filename > last_path){
                            repoData.setStrategy(RepoData::ExtractorTXTType, filename, "", "");
                            df = repoData.extractData();
                            outQueues.enQueue(std::make_pair(key, df));

                            if ( filename > max_path ) {
                                max_path = filename;
                            }
                        }
                    }

                    map_mutex.set("datacat_behaviour", max_path);
                    lock.unlock();
                }
            }
        }

        MapMutex<std::string> &map_mutex;
};
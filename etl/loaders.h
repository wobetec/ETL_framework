#include "../src/framework.h"
#include "object.h"
#include <iostream>
#include <string>
#include <filesystem>

class LoaderThreds : public ThreadWrapper<Queue<std::string, DataFrame<Object>>, Queue<std::string, DataFrame<Object>>> {
    public:
        LoaderThreds(
            Queue<std::string, DataFrame<Object>> &inQueue
        ) : ThreadWrapper(inQueue, outQueues) {}

        void run() override {
            while (running) {
                std::cout << "Loading data" << std::endl;

                std::pair<std::string, DataFrame<Object>> data = inQueue.deQueue();
                outQueues.enQueue(data);
            }
        }
};
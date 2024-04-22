#include "../src/framework.h"
#include "object.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "../src/db.h"

class LoaderThreds : public ThreadWrapper<Queue<std::string, DataFrame<Object>>, Queue<std::string, DataFrame<Object>>> {
    public:
        LoaderThreds(
            Queue<std::string, DataFrame<Object>> &inQueue
        ) : ThreadWrapper(inQueue, outQueues) {}

        ~LoaderThreds() {
            running = false;
            join();
        }

        void join() {
            if (handler_thread.joinable()) {
                handler_thread.join();
            }
        }

        void run() override {
            DB db("new.db");
            while (running) {
                std::cout << "Loading data" << std::endl;

                std::pair<std::string, DataFrame<Object>> data = inQueue.deQueue();
                outQueues.enQueue(data);
            }
        }
};
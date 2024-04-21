#pragma once

#include <map>
#include "dataframe.h"
#include "queue.h"
#include <thread>
#include <iostream>
#include <string>

template <typename T>
class Handler {
    public:
        Handler(
            Queue<std::string, DataFrame<T>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<T>> &> outQueues
        ) : inQueue(inQueue), outQueues(outQueues) {}

        ~Handler() { join(); }
        
        void join() {
            if (handler_thread.joinable()) {
                handler_thread.join();
            }
        }

        virtual void run() = 0;

        void start() {
            handler_thread = std::thread(&Handler::run, this);
        }

        Queue<std::string, DataFrame<T>> &inQueue;
        std::map<std::string, Queue<std::string, DataFrame<T>>&> outQueues;

        std::thread handler_thread;
        bool running;

    private:
};

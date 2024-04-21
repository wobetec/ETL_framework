#pragma once

#include <map>
#include "dataframe.h"
#include "queue.h"

template <typename T>
class Handler {
    public:
        Handler(Queue<std::string, DataFrame<T>>& inQueue, std::map<std::string, Queue<std::string, DataFrame<T>>>& outQueues) : inQueue(inQueue), outQueues(outQueues) {
            running = true;
        }

        ~Handler() { join(); }

        void start() {
            handler_thread = std::thread(&Handler::run, this);
        }

        void join() {
            if (handler_thread.joinable()) {
                handler_thread.join();
            }
        }

        virtual void run() = 0;
    
        Queue<std::string, DataFrame<T>>& inQueue;
        std::map<std::string, Queue<std::string, DataFrame<T>>>& outQueues;

        std::thread handler_thread;
        bool running;

    private:
};

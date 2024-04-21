// Handler.h

#ifndef HANDLER_H
#define HANDLER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include "dataframe.h"
#include "queue.h"

template <typename T>
class Handler {
public:
    Handler(Queue<int, DataFrame<T>>& inQueue, Queue<int, DataFrame<T>>& outQueue)
        : inQueue_(inQueue), outQueue_(outQueue), terminate_(false) {}

    ~Handler() {
        if (thread_.joinable()) {
            terminate_ = true;
            thread_.join();
        }
    }

    void start() {
        thread_ = std::thread(&Handler::run, this);
    }

    void inQueue(DataFrame<T> df) {
        inQueue_.enQueue(df);
    }

    DataFrame<T> outQueue() {
        return outQueue_.deQueue();
    }

private:
    void run() {
        while (!terminate_) {
            DataFrame<T> df = inQueue_.deQueue();
            DataFrame<T> processed_df = processDataFrame(df);
            outQueue_.enQueue(std::move(processed_df));
        }
    }

    DataFrame<T> processDataFrame(DataFrame<T>& df) {
        return df;
    }

    Queue<int, DataFrame<T>>& inQueue_;
    Queue<int, DataFrame<T>>& outQueue_;
    std::thread thread_;
    bool terminate_;
};

#endif
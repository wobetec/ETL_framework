// Handler.h

#ifndef HANDLER_H
#define HANDLER_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
// #include "DataFrame.h"

template <typename T>
class DataFrame;
template <typename T>
class Handler {
public:
    Handler();
    ~Handler();

    void start();
    void inQueue(DataFrame<T> df);
    DataFrame<T> outQueue();

private:
    void run();
    void __run();
    DataFrame<T> processDataFrame(DataFrame<T>& df);
    std::queue<DataFrame<T>> inQueue_;
    std::queue<DataFrame<T>> outQueue_;
    std::thread thread_;
    std::mutex inMutex_;
    std::mutex outMutex_;
    std::condition_variable cv_;
    bool terminate_ = false;
};

#include "handler.cpp" 

#endif

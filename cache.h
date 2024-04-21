#ifndef CACHE_H
#define CACHE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
// #include "DataFrame.h"

class DataFrame;

template <typename T>
class Cache {
public:
    Cache();
    ~Cache();

    void start();
    void addData(const T& data);
    T getData();

private:
    void processCacheEntries();

    std::queue<T> inQueue_;
    std::queue<T> outQueue_;
    std::thread thread_;
    std::mutex inMutex_;
    std::mutex outMutex_;
    std::condition_variable inCv_;
    std::condition_variable outCv_;
    bool terminate_ = false;
};

#include "cache.cpp"

#endif

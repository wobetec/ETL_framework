#include "cache.h"

template <typename T>
Cache<T>::Cache() : terminate_(false) {}

template <typename T>
Cache<T>::~Cache() {
    if (thread_.joinable()) {
        terminate_ = true;
        inCv_.notify_all();
        outCv_.notify_all();
        thread_.join();
    }
}

template <typename T>
void Cache<T>::start() {
    thread_ = std::thread(&Cache<T>::processCacheEntries, this);
}

template <typename T>
void Cache<T>::addData(const T& data) {
    std::lock_guard<std::mutex> lock(inMutex_);
    inQueue_.push(data);
    inCv_.notify_one();
}

template <typename T>
T Cache<T>::getData() {
    std::unique_lock<std::mutex> lock(outMutex_);
    outCv_.wait(lock, [this]() { return !outQueue_.empty() || terminate_; });
    if (terminate_) {
        return T();
    }
    T data = outQueue_.front();
    outQueue_.pop();
    return data;
}

template <typename T>
void Cache<T>::processCacheEntries() {
    while (!terminate_) {
        std::unique_lock<std::mutex> lock(inMutex_);
        inCv_.wait(lock, [this]() { return !inQueue_.empty() || terminate_; });
        if (terminate_) {
            break;
        }
        T data = inQueue_.front();
        inQueue_.pop();
        lock.unlock();

        std::lock_guard<std::mutex> outLock(outMutex_);
        outQueue_.push(data);
        outCv_.notify_one();
    }
}

template class Cache<DataFrame>;

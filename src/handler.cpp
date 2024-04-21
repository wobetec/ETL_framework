// Handler.cpp

#include "handler.h"

template <typename T>
class DataFrame {
public:
};

template <typename T>
Handler<T>::Handler() : terminate_(false) {}

template <typename T>
Handler<T>::~Handler() {
    if (thread_.joinable()) {
        terminate_ = true;
        cv_.notify_all();
        thread_.join();
    }
}

template <typename T>
void Handler<T>::start() {
    thread_ = std::thread(&Handler::run, this);
}

template <typename T>
void Handler<T>::inQueue(DataFrame<T> df) {
    std::lock_guard<std::mutex> lock(inMutex_);
    inQueue_.push(std::move(df));
    cv_.notify_one();
}

template <typename T>
DataFrame<T> Handler<T>::outQueue() {
    std::unique_lock<std::mutex> lock(outMutex_);
    cv_.wait(lock, [this]() { return !outQueue_.empty() || terminate_; });
    if (terminate_) {
        return DataFrame<T>();
    }
    DataFrame<T> df = std::move(outQueue_.front());
    outQueue_.pop();
    return df;
}

template <typename T>
void Handler<T>::run() {
    while (!terminate_) {
        std::unique_lock<std::mutex> lock(inMutex_);
        cv_.wait(lock, [this]() { return !inQueue_.empty() || terminate_; });
        if (terminate_) {
            break;
        }
        DataFrame<T> df = std::move(inQueue_.front());
        inQueue_.pop();
        lock.unlock();

        DataFrame<T> processed_df = processDataFrame(df);

        std::lock_guard<std::mutex> outLock(outMutex_);
        outQueue_.push(std::move(processed_df));
    }
}

template <typename T>
void Handler<T>::__run() {
}

template <typename T>
DataFrame<T> Handler<T>::processDataFrame(DataFrame<T>& df) {
    return df;
}

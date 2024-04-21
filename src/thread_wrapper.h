#pragma once

#include <thread>

template <typename T, typename U>
class ThreadWrapper {
    public:
        ThreadWrapper(
            T &inQueue,
            U &outQueues
        ) : inQueue(inQueue), outQueues(outQueues) {}

        ~ThreadWrapper() { 
            running = false;
            join(); 
        }
        
        void join() {
            if (thread.joinable()) {
                thread.join();
            }
        }

        virtual void run() = 0;

        void start() {
            thread = std::thread(&ThreadWrapper::run, this);
        }

        T &inQueue;
        U &outQueues;

        bool running = true;
    private:
        std::thread thread;
};


template <typename T>
class MapMutex {
    public:
        MapMutex() {}
        ~MapMutex() {}

        std::unique_lock<std::mutex> getLock(std::string table) {
            return std::unique_lock<std::mutex>(mutexes[table]);
        }

        T get(std::string key) {
            return data[key];
        }

        void set(std::string key, T value) {
            data[key] = value;
        }

    private:
        std::map<std::string, std::mutex> mutexes;
        std::map<std::string, T> data;
};

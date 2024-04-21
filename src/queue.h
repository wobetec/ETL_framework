#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <stdexcept>

template <typename U, typename V>
class Queue {
    /**
     * @brief Implement the queue data structure. 
     * 
     * Have the responsability to control the access to 
     * the queue and handle concurrency problems.
     */
    public:
        Queue(int capacity) : capacity(capacity) {}
        ~Queue() {
            queue_mutex.lock();
            while(queue.size() > 0) {
                queue.pop();
            }
            queue_mutex.unlock();
        }

        void enQueue(std::pair<U, V> item) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this] { return queue.size() < capacity; });

            queue.push(item);

            lock.unlock();
            cv.notify_all();
        }

        std::pair<U, V> deQueue(){
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this] { return queue.size() > 0; });

            std::pair<U, V> pop = queue.front();
            queue.pop();

            lock.unlock();
            cv.notify_all();

            return pop;
        }

    private:
        std::mutex queue_mutex;
        std::condition_variable cv;
        int capacity;
        std::queue<std::pair<U, V>> queue;
};

#include "queue.h"

void queueT::enQueue(pair<string, string> data) {
    Mutex.lock();
    if(size == capacity) {
        printf("OVERFLOW\n");
        return;
    }
    queue.push_back(data);
    size += 1;
    Mutex.unlock();
}

pair<string, string> queueT::deQueue() {
    Mutex.lock();
    if(size == 0) {
        printf("UNDERFLOW\n");
        return make_pair("NULL", "NULL");
    }
    pair<string, string> pop = queue.front();
    queue.erase(queue.begin());
    size -= 1;
    
    Mutex.unlock();
    return pop;
}

void queueT::printQueue() {
    for (const pair<string, string>& element : queue) {
        std::cout << element.first << " " << element.second << endl;
    }
    cout << endl;
}
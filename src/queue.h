#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <vector>
#include <mutex>

using namespace std;

class queueT {
    public:
        vector<pair<string, string>> queue;
        int size = 0;
        int capacity = 1000;
        mutex Mutex;
        void enQueue(pair<string, string> data);
        pair<string, string> deQueue();
        void printQueue();
};

#endif
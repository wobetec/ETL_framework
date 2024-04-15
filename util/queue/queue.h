#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include <thread>
#include <set>
#include <vector>

using namespace std;

class queueT {
    public:
        pair<string, string> data;
        void Enqueue(pair<string, string> data);
};

#endif
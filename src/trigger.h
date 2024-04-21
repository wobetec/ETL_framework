#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include "queue.h"

namespace fs = filesystem;

typedef Queue<std::string, std::string> QueueTrigger;

class Trigger {
    public:
        Trigger(QueueTrigger &outQueue, std::string first, std::string second) : outQueue(outQueue), first(first), second(second) {}
        ~Trigger() { 
            running = false;
            join(); 
        }
        
        void join() {
            if (trigger_thread.joinable()) {
                trigger_thread.join();
            }
        }

        virtual void run() = 0;

        void start() {
            trigger_thread = std::thread(&Trigger::run, this);
        }

        void addToQueue(){
            outQueue.enQueue(std::make_pair(first, second));
        }

        Queue &outQueue;
        bool running = true;
        std::string first;
        std::string second;

    private:
        std::thread trigger_thread;
};

class TimeTrigger : public Trigger {
    public:
        TimeTrigger(QueueTrigger outQueue, int interval, std::string first, std::string second) : Trigger(outQueue, first, second), interval(interval) {}

        void run() {
            while(running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }
        }

    private:
        int interval = 0;
};

class RequestTrigger : public Trigger {
    public:
        RequestTrigger(QueueTrigger outQueue, std::string first, std::string second) : Trigger(outQueue, first, second) {}

        void request() {
            addToQueue();
        }
    private:
};

#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <set>
#include <vector>

using namespace std;
namespace fs = filesystem;

class Trigger {
    public:
        queueT* outQueue;
        string path;
        int running = 1;
        void addToQueue(pair<string, string> data);
        void run();
};

class TimeTrigger : public Trigger {
    public:
        int time_interval = 1000;
        void check();
        void run(); 
};

class FolderTimeTrigger : public TimeTrigger {
    public: 
        set<string> known_files;
        void check();
        void run();
};

class CSVTimeTrigger : public TimeTrigger {
    public: 
        void check();
        void run();
        
};

class RequestTrigger : public Trigger {
    public:
        int request = 0;
        void check();
        void run();
};

#endif 
#include "queue.h"
#include "./trigger.h"


class Trigger {
    public:
        queueNode* outQueue;
        thread Thread;
        string path;
        int running = 1;
        void addToQueue(pair<string, string> data) {
            outQueue->Enqueue(data);
        }
        void run();
        void join() {
            Thread.join();
        }
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

        // look for new files in the folder in 'dir'
        void check() {
            for (const auto & entry : fs::directory_iterator(path))
                if(known_files.find(entry.path()) == known_files.end())
                {
                    known_files.insert(entry.path());
                    addToQueue(make_pair(string(entry.path()), "txt"));
                } 
        }
        void run() {
            while(running) {
                check();
                this_thread::sleep_for(chrono::milliseconds(time_interval));
            }
        }
};


class CSVTimeTrigger : public TimeTrigger {
    public: 
        void check() {
            addToQueue(make_pair(path, "csv"));
        }

        void run() {
            while(running) {
                check();
                this_thread::sleep_for(chrono::milliseconds(time_interval));
            }
        }
};


class RequestTrigger : public Trigger {
    public:
        int request = 0;
        void check() {
            if(request) {
                addToQueue(make_pair(path, "sql"));
            }
        }
        void run() {
            while(running)
                check();
        }
};
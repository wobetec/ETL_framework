#include "./queue.h"
#include "./trigger.h"


int isTxt(string filename) {
    int n = filename.length();
    if(filename[n-1] == 't' && filename[n-2] == 'x' && 
        filename[n-3] == 't' && filename[n-4] == '.') {
        return 1;
    }
    return 0;
}

void Trigger::addToQueue(pair<string, string> data) {
    outQueue->enQueue(data);
}

void FolderTimeTrigger::check() {
    for (const auto & entry : fs::directory_iterator(path)) {
        string filename = string(entry.path());
        if(known_files.find(filename) == known_files.end()) {
            known_files.insert(filename);
            if(isTxt(filename)) 
                addToQueue(make_pair(filename, "txt"));
        } 
    }
}

void FolderTimeTrigger::run() {
    while(running) {
        check();
        this_thread::sleep_for(chrono::milliseconds(time_interval));
    }
}

void CSVTimeTrigger::check() {
    addToQueue(make_pair(path, "csv"));
    return;
}

void CSVTimeTrigger::run() {
    while(running) {
        check();
        this_thread::sleep_for(chrono::milliseconds(time_interval));
    }
}

void RequestTrigger::check() {
    if(request) {
        addToQueue(make_pair(path, "sql"));
    }
}

void RequestTrigger::run() {
    while(running)
        check();
}

int main() {
    queueT output;

    FolderTimeTrigger fold;
    CSVTimeTrigger cs;
    RequestTrigger req;

    fold.path = "./";
    fold.outQueue = &output;

    cs.path = "./";
    cs.outQueue = &output;

    req.path = "./";
    req.outQueue = &output;

    thread Thread1(&FolderTimeTrigger::run, &fold);
    thread Thread2(&CSVTimeTrigger::run, &cs);
    thread Thread3(&RequestTrigger::run, &req);

    Thread1.join();
    Thread2.join();
    Thread3.join();
    
    return 0;
}
#include "queue.h"

class queueT {
    public:
        vector<pair<string, string>> queue;
        int empty = 1;
        int full = 0;
        int N_items = 0;

        void enqueue(pair<string, string> data) {
            cout << "TESTE";
        }
        void dequeue();
        void up_mutex();
        void down_mutex();
        void up_full();
        void down_full();
        void up_empty();
        void down_empty();
};
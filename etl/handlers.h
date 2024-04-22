#include <iostream>
#include <map>
#include <string>
#include "../src/framework.h"
#include "object.h"
#include <chrono>

typedef std::pair<std::string, DataFrame<Object>> QueueItem;

class HandlerSpliter : public Handler<Object> {
    public:
        HandlerSpliter(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>>*> outQueues
        ) : Handler(inQueue, outQueues) {}

        void run() {
            while (running) {
                std::cout << "Handler running Spliter" << std::endl;
                QueueItem item = inQueue.deQueue();
                auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string key = item.first;
                item.first = std::to_string(now);
                outQueues[key]->enQueue(item);
            }
        }
};

class HandlerCDatacat : public Handler<Object> {
    public:
        HandlerCDatacat(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>>*> outQueues
        ) : Handler(inQueue, outQueues) {}

        void run() override {
            while (running) {
                std::cout << "Handler running CDatacat" << std::endl;
                
                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                df_in = df_in.filter<std::string>("stimulus", "==", "Visualization");

                Series<Object> message = df_in["message"];
                std::vector<Object> product_id = {};
                for (int i = 0; i < message.data.size(); i++) {
                    std::string m = std::get<std::string>(message[i]);
                    int len = m.length();
                    product_id.push_back(m.substr(len-5).substr(0, 4));
                }

                DataFrame<Object> df_out;
                df_out.addColumn("product_id", product_id);
                df_out.addColumn("user_id", df_in["user_id"]);
                df_out.addColumn("notification_date", df_in["notification_date"]);

                outQueues["s_vis"]->enQueue(std::make_pair(item.first, df_out));
            }
        }
};

class HandlerCCade : public Handler<Object> {
    public:
        HandlerCCade(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues
        ) : Handler(inQueue, outQueues) {}

        void run() override {
            while (running) {
                std::cout << "Handler running CCade" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;
                Series<Object> message = df_in["stimulus"];

                std::vector<Object> visualized = {};
                std::vector<Object> product_id = {};
                for (int i = 0; i < message.data.size(); i++) {
                    std::string m = std::get<std::string>(message[i]);
                    int len = m.length();
                    if (len >= 10 && m.substr(0, 10) == "Visualized") {
                        visualized.push_back(true);
                        product_id.push_back(m.substr(len - 6).substr(0, 4));
                    } else {
                        visualized.push_back(false);
                        product_id.push_back("");
                    }
                }
                df_in.addColumn("visualized", visualized);
                df_in.addColumn("product_id", product_id);
                df_in = df_in.filter<bool>("visualized", "==", true);

                DataFrame<Object> df_out;
                df_out.addColumn("product_id", df_in["product_id"]);
                df_out.addColumn("user_id", df_in["user_id"]);
                df_out.addColumn("notification_date", df_in["notification_date"]);

                outQueues["s_vis"]->enQueue(std::make_pair(item.first, df_out));
            }
        }
};

class HandlerSVis : public Handler<Object> {
    public:
        HandlerSVis(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running SVis" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;
                // df_in.print();

                std::unique_lock<std::mutex> lock = cache.getLock("visualizacoes");

                DataFrame<Object> df_cache = cache.read("visualizacoes");

                DataFrame<Object> df_out = df_in.concat(df_cache);
                
                df_out = df_out.dropDuplicate({"product_id", "user_id", "notification_date"});

                std::vector<DefaultObject> filter = {};
                DateTime now = DateTime();
                for (int i = 0; i < df_out.shape.first; i++) {
                    DateTime dt(std::get<std::string>(df_out["notification_date"][i]));
                    dt.replace(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), 0);
                    
                    if ((now - dt).seconds() > TimeDelta(60 * 60).seconds()) {
                        filter.push_back(false);
                    } else {
                        filter.push_back(true);
                    }

                    df_out["notification_date"][i] = Object(dt.strftime());
                }

                df_out = df_out.filter(Series<DefaultObject>(filter));

                cache.save("visualizacoes", df_out);

                lock.unlock();

                outQueues["t_1"]->enQueue(std::make_pair(item.first, df_out));
                outQueues["t_3"]->enQueue(std::make_pair(item.first, df_out));
                outQueues["t_5"]->enQueue(std::make_pair(item.first, df_out));
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerSProdutos : public Handler<Object> {
    public:
        HandlerSProdutos(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running SProdutos" << std::endl;
                
                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                DataFrame<Object> df_out;
                df_out.addColumn("product_id", df_in["product_id"]);
                df_out.addColumn("name", df_in["name"]);

                std::unique_lock<std::mutex> lock = cache.getLock("produtos");

                cache.save("produtos", df_in);

                lock.unlock();
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerSEstoque : public Handler<Object> {
    public:
        HandlerSEstoque(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running SEstoque" << std::endl;
                
                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                df_in.addColumn("available_quantity", df_in["available_quantity"].astype<std::string, int>());

                std::unique_lock<std::mutex> lock = cache.getLock("estoque");

                cache.save("estoque", df_in);

                lock.unlock();
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerSCompras : public Handler<Object> {
    public:
        HandlerSCompras(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running SCompras" << std::endl;
                
                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;


                std::unique_lock<std::mutex> lock = cache.getLock("compras");

                DataFrame<Object> df_cache = cache.read("compras");

                // do something with cache

                cache.save("compras", df_in);

                lock.unlock();

                outQueues["t_2"]->enQueue(std::make_pair(item.first, df_in));
                outQueues["t_4"]->enQueue(std::make_pair(item.first, df_in));
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerA1 : public Handler<Object> {
    public:
        HandlerA1(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues
        ) : Handler(inQueue, outQueues){}

        void run() override {
            while (running) {
                std::cout << "Handler running A1" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df = item.second;

                std::cout << "HandlerA1: " << item.first << std::endl;
                
                df = df.count<std::string>("notification_date");
           
                outQueues["load"]->enQueue(std::make_pair(item.first, df));
                outQueues["t_6"]->enQueue(std::make_pair(item.first, df));
            }
        }
};

class HandlerA2 : public Handler<Object> {
    public:
        HandlerA2(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running A2" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                std::unique_lock<std::mutex> lock = cache.getLock("compras_media");

                DataFrame<Object> df_cache = cache.read("compras_media");

                // do something with cache

                cache.save("compras_media", df_in);

                lock.unlock();

                outQueues["load"]->enQueue(std::make_pair(item.first, df_in));
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerA3 : public Handler<Object> {
    public:
        HandlerA3(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues
        ) : Handler(inQueue, outQueues){}

        void run() override {
            while (running) {
                std::cout << "Handler running A3" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                // do something with df_in
                df_in = df_in.dropDuplicate({"user_id", "project_id"});
                df_in = df_in.count<std::string>("notification_date");


                outQueues["load"]->enQueue("load", df_in);
            }
        }
};

class HandlerA4 : public Handler<Object> {
    public:
        HandlerA4(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running A4" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                std::cout << "HandlerA4: " << item.first << std::endl;

                std::unique_lock<std::mutex> lock = cache.getLock("produtos");
                DataFrame<Object> df_cache = cache.read("produtos");
                lock.unlock();

                // do something with df_in and df_cache

                outQueues["load"]->enQueue(std::make_pair(item.first, df_in));
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerA5 : public Handler<Object> {
    public:
        HandlerA5(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache){}

        void run() override {
            while (running) {
                std::cout << "Handler running A5" << std::endl;
                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                df_in = df_in.count<std::string>("product_id");

                std::unique_lock<std::mutex> lock = cache.getLock("produtos");
                DataFrame<Object> df_cache = cache.read("produtos");
                lock.unlock();

                if (df_cache.shape.first == 0) {
                    continue;
                }

                DataFrame<Object> df_out = df_in.merge<std::string>(df_cache, "product_id", "product_id");

                outQueues["load"]->enQueue(std::make_pair(item.first, df_out));
            }
        }

        private:
            Cache<Object> &cache;
};

class HandlerA6 : public Handler<Object> {
    public:
        HandlerA6(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running A6" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                std::cout << "HandlerA6: " << item.first << std::endl;

                std::unique_lock<std::mutex> lock = cache.getLock("compras_media");
                DataFrame<Object> df_cache = cache.read("compras_media");
                lock.unlock();

                // do something with df_in and df_cache

                outQueues["load"]->enQueue(std::make_pair(item.first, df_in));
            }
        }

    private:
        Cache<Object> &cache;
};

class HandlerA7 : public Handler<Object> {
    public:
        HandlerA7(
            Queue<std::string, DataFrame<Object>> &inQueue,
            std::map<std::string, Queue<std::string, DataFrame<Object>> *> outQueues,
            Cache<Object> &cache
        ) : Handler(inQueue, outQueues), cache(cache) {}

        void run() override {
            while (running) {
                std::cout << "Handler running A7" << std::endl;

                QueueItem item = inQueue.deQueue();
                DataFrame<Object> df_in = item.second;

                std::cout << "HandlerA7: " << item.first << std::endl;

                std::unique_lock<std::mutex> lock = cache.getLock("produtos");
                DataFrame<Object> df_cache = cache.read("produtos");
                lock.unlock();

                // do something with df_in and df_cache

                outQueues["load"]->enQueue(std::make_pair(item.first, df_in));
            }
        }

    private:
        Cache<Object> &cache;
};
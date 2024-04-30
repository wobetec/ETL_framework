#include <iostream>
#include <map>
#include "../src/framework.h"
#include "handlers.h"
#include "object.h"
#include "extractors.h"
#include "loaders.h"

#define DEFAULT_QUEUE_SIZE 5

using namespace std;

int main(){

    // Triggers
    // Extract
    Queue<string, string> q_trigger(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_extract(DEFAULT_QUEUE_SIZE);

    TimeTrigger tg_datacat(q_trigger, 1000, "datacat", "extract");
    TimeTrigger tg_produtos(q_trigger, 1000, "produtos", "extract");
    TimeTrigger tg_estoque(q_trigger, 1000, "estoque", "extract");
    TimeTrigger tg_compras(q_trigger, 1000, "compras", "extract");
    RequestTrigger tg_cade(q_trigger, "cade", "extract");

    tg_datacat.start();
    tg_produtos.start();
    tg_estoque.start();
    tg_compras.start();

    MapMutex<string> map_mutex;

    ExtractThread t_extract_1(q_trigger, q_extract, map_mutex);
    t_extract_1.start();

    ExtractThread t_extract_2(q_trigger, q_extract, map_mutex);
    t_extract_2.start();

    ExtractThread t_extract_3(q_trigger, q_extract, map_mutex);
    t_extract_3.start();

    ExtractThread t_extract_4(q_trigger, q_extract, map_mutex);
    t_extract_4.start();


    // // Spliter
    Queue<string, DataFrame<Object>> q_datacat(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_cade(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_produtos(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_estoque(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_compras(DEFAULT_QUEUE_SIZE);

    HandlerSpliter t_spliter(q_extract, {
        {"datacat", &q_datacat},
        {"cade", &q_cade},
        {"produtos", &q_produtos},
        {"estoque", &q_estoque},
        {"compras", &q_compras}
    });
    t_spliter.start();
    
    // Preprocessor
    Queue<string, DataFrame<Object>> q_s_vis(DEFAULT_QUEUE_SIZE);

    HandlerCDatacat t_datacat(q_datacat, {
        {"s_vis", &q_s_vis}
    });
    t_datacat.start();

    HandlerCCade t_cade(q_cade, {
        {"s_vis", &q_s_vis}
    });
    t_cade.start();

    // Save
    Cache<Object> cache;

    Queue<string, DataFrame<Object>> q_t_1(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_2(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_3(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_4(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_5(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_6(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<Object>> q_t_7(DEFAULT_QUEUE_SIZE);

    HandlerSVis t_s_vis(q_s_vis, {
        {"t_1", &q_t_1},
        {"t_3", &q_t_3},
        {"t_5", &q_t_5}
    },
    cache);
    t_s_vis.start();

    HandlerSEstoque t_s_estoque(q_estoque, {}, cache);
    t_s_estoque.start();
    
    HandlerSCompras t_s_compras(q_compras, {
        {"t_2", &q_t_2},
        {"t_4", &q_t_4},
    },
    cache);
    t_s_compras.start();

    HandlerSProdutos t_s_produtos(q_produtos, {}, cache);
    t_s_produtos.start();

    // Analyze
    Queue<string, DataFrame<Object>> q_load(DEFAULT_QUEUE_SIZE);

    HandlerA1 t_a1(q_t_1, {{"load", &q_load}, {"t_6", &q_t_6}});
    t_a1.start();

    HandlerA2 t_a2(q_t_2, {{"load", &q_load}}, cache);
    t_a2.start();

    HandlerA3 t_a3(q_t_3, {{"load", &q_load}});
    t_a3.start();

    HandlerA4 t_a4(q_t_4, {{"load", &q_load}}, cache);
    t_a4.start();

    HandlerA5 t_a5(q_t_5, {{"load", &q_load}}, cache);
    t_a5.start();

    HandlerA6 t_a6(q_t_6, {{"load", &q_load}}, cache);
    t_a6.start();

    // Load
    // LoaderThreads t_load(q_load);
    // t_load.start();

    // Simulate
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        tg_cade.run();
    }

    t_extract_1.join();
    t_extract_2.join();
    t_extract_3.join();
    t_extract_4.join();

    tg_datacat.join();
    tg_produtos.join();
    tg_estoque.join();
    tg_compras.join();

    t_spliter.join();
    t_datacat.join();
    t_cade.join();
    t_s_vis.join();
    t_s_compras.join();
    t_s_estoque.join();
    t_s_produtos.join();
    t_a1.join();
    t_a2.join();
    t_a3.join();
    t_a4.join();
    t_a5.join();
    t_a6.join();

    // t_load.join();
    
    return 0;
}
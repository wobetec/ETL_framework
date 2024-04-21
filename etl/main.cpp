#include <iostream>
#include <map>
#include "../src/framework.h"
#include "handlers.h"

#define DEFAULT_QUEUE_SIZE 5

using namespace std;

int main(){

    // Extract
    Queue<string, DataFrame<DefaultObject>> q_extract(DEFAULT_QUEUE_SIZE);

    // Spliter
    Queue<string, DataFrame<DefaultObject>> q_datacat(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_cade(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_produtos(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_estoque(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_compras(DEFAULT_QUEUE_SIZE);

    HandlerSpliter t_spliter(q_extract, {
        {"datacat", q_datacat},
        {"cade", q_cade},
        {"produtos", q_produtos},
        {"estoque", q_estoque},
        {"compras", q_compras}
    });
    t_spliter.start();

    // Preprocessor
    Queue<string, DataFrame<DefaultObject>> q_s_vis(DEFAULT_QUEUE_SIZE);

    HandlerCDatacat t_datacat(q_datacat, {
        {"s_vis", q_s_vis}
    });
    t_datacat.start();

    HandlerCCade t_cade(q_cade, {
        {"s_vis", q_s_vis}
    });
    t_cade.start();

    // Save
    Cache<DefaultObject> cache;

    Queue<string, DataFrame<DefaultObject>> q_t_1(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_2(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_3(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_4(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_5(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_6(DEFAULT_QUEUE_SIZE);
    Queue<string, DataFrame<DefaultObject>> q_t_7(DEFAULT_QUEUE_SIZE);

    HandlerSVis t_s_vis(q_s_vis, {
        {"t_1", q_t_1},
        {"t_3", q_t_3},
        {"t_5", q_t_5}
    },
    cache);
    t_s_vis.start();

    HandlerSCompras t_s_compras(q_compras, {
        {"t_2", q_t_2},
        {"t_4", q_t_4},
    },
    cache);
    t_s_compras.start();
    
    HandlerSEstoque t_s_estoque(q_estoque, {}, cache);
    t_s_estoque.start();

    HandlerSProdutos t_s_produtos(q_produtos, {}, cache);
    t_s_produtos.start();

    // Analyze
    Queue<string, DataFrame<DefaultObject>> q_load(DEFAULT_QUEUE_SIZE);

    HandlerA1 t_a1(q_t_1, {{"load", q_load}, {"t_6", q_t_6}});
    t_a1.start();

    HandlerA2 t_a2(q_t_2, {{"load", q_load}}, cache);
    t_a2.start();

    HandlerA3 t_a3(q_t_3, {{"load", q_load}});
    t_a3.start();

    HandlerA4 t_a4(q_t_4, {{"load", q_load}}, cache);
    t_a4.start();

    HandlerA5 t_a5(q_t_5, {{"load", q_load}});
    t_a5.start();

    HandlerA6 t_a6(q_t_6, {{"load", q_load}}, cache);
    t_a6.start();

    HandlerA7 t_a7(q_t_7, {{"load", q_load}}, cache);
    t_a7.start();

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
    t_a7.join();

    return 0;
}
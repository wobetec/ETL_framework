#include "../../src/DataFrame.h"
#include "../../src/utils/datetime.h"
#include "../../src/utils/char_types.h"
#include <iomanip>

struct CadeAnalytics{
    int id_usuario;
    string32 estimulo;
    string32 component_alvo;
    DateTime data_notificacao;
} typedef CadeAnalytics;

class DF_CadeAnalytics : public DataFrame<CadeAnalytics> {
    private:
        std::vector<CadeAnalytics> data;
        int print_width[4] = {20, 3, 32, 32};

    public:
        void print();
        void append(CadeAnalytics data);
        int size();
        std::string type();
        DF_CadeAnalytics concat(DF_CadeAnalytics &df);
};
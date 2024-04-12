#include "../../src/DataFrame.h"
#include "../../src/utils/datetime.h"
#include <iomanip>

struct CadeAnalytics{
    DateTime data_notificacao;
    int id_usuario;
    char estimulo[20];
    char component_alvo[20];
} typedef CadeAnalytics;

class DF_CadeAnalytics : public DataFrame<CadeAnalytics> {
    private:
        std::vector<CadeAnalytics> data;
    public:
        void print() {
            std::cout 
                << std::right << std::setw(3) << ""
                << std::right << std::setw(20) << "Data Notificacao" 
                << std::right << std::setw(3) << "ID"
                << std::right << std::setw(20) << "Estimulo"
                << std::right << std::setw(20) << "Componente Alvo"
                << std::endl;
            for (int i = 0; i < data.size(); i++) {
                std::cout 
                    << std::right << std::setw(3) << i
                    << std::right << std::setw(20) << data[i].data_notificacao.strftime()
                    << std::right << std::setw(3) << data[i].id_usuario
                    << std::right << std::setw(20) << data[i].estimulo
                    << std::right << std::setw(20) << data[i].component_alvo
                    << std::endl;
            }
        }
        void append(CadeAnalytics data) {
            this->data.push_back(data);
        }
        int size() {
            return data.size();
        }
};
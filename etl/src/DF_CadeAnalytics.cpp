#include "./DF.h"

void DF_CadeAnalytics::print() {
    std::cout 
        << std::right << std::setw(4) << ""
        << std::right << std::setw(print_width[0]) << "Data Notificacao" 
        << std::right << std::setw(print_width[1]) << "ID"
        << std::right << std::setw(print_width[2]) << "Estimulo"
        << std::right << std::setw(print_width[3]) << "Componente Alvo"
        << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout 
            << std::right << std::setw(4) << i
            << std::right << std::setw(print_width[0]) << data[i].data_notificacao.strftime()
            << std::right << std::setw(print_width[1]) << data[i].id_usuario
            << std::right << std::setw(print_width[2]) << data[i].estimulo
            << std::right << std::setw(print_width[3]) << data[i].component_alvo
            << std::endl;
    }
}

void DF_CadeAnalytics::append(CadeAnalytics data) {
    this->data.push_back(data);
}

int DF_CadeAnalytics::size() {
    return data.size();
}

std::string DF_CadeAnalytics::type() {
    return "CadeAnalytics";
}

DF_CadeAnalytics DF_CadeAnalytics::concat(DF_CadeAnalytics &df) {
    DF_CadeAnalytics *df_cade = new DF_CadeAnalytics();
    for (int i = 0; i < this->size(); i++) {
        df_cade->append(this->data[i]);
    }
    for (int i = 0; i < df.size(); i++) {
        df_cade->append(df.data[i]);
    }
    return *df_cade;
}
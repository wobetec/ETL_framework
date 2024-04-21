#pragma once

#include <mutex>
#include <map>
#include "dataframe.h"

template <typename T>
class Cache {
    public:
        Cache() {};
        ~Cache() {
            cache.clear();
            mutex_cache.clear();
        };

        void save(std::string table, DataFrame<T> data) {
            cache[table] = data;
        }

        DataFrame<T> read(std::string table) {
            auto it = cache.find(table);
            if (it == cache.end()) {
                return DataFrame<T>();
            }
            return cache[table];
        }

        std::unique_lock<std::mutex> getLock(std::string table) {
            return std::unique_lock<std::mutex>(mutex_cache[table]);
        }

    private:
        std::map<std::string, DataFrame<T>> cache;
        std::map<std::string, std::mutex> mutex_cache;
};

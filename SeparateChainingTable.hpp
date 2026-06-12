#ifndef SEPARATECHAININGTABLE_HPP
#define SEPARATECHAININGTABLE_HPP

#include "IHashTable.hpp"
#include <vector>
#include <algorithm>

class SeparateChainingTable : public IHashTable {
private:
    std::vector<std::vector<std::string>> table;

public:
    SeparateChainingTable(int s) : IHashTable(s) {
        table.resize(size);
    }

    void insert(const std::string& key) override {
        int idx = getBaseHash(key);
        // Dodajemy na koniec listy pod danym indeksem
        table[idx].push_back(key);
    }

    bool remove(const std::string& key) override {
        int idx = getBaseHash(key);
        auto& chain = table[idx];
        auto it = std::find(chain.begin(), chain.end(), key);
        if (it != chain.end()) {
            chain.erase(it);
            return true;
        }
        return false; // Nie znaleziono elementu
    }

    bool search(const std::string& key) override {
        int idx = getBaseHash(key);
        const auto& chain = table[idx];
        return std::find(chain.begin(), chain.end(), key) != chain.end();
    }
};

#endif
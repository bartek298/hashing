#ifndef SEPARATECHAININGTABLE_HPP
#define SEPARATECHAININGTABLE_HPP

#include "IHashTable.hpp"
#include <vector>
#include <algorithm>

class SeparateChainingTable : public IHashTable {
private:
    std::vector<std::vector<int>> table;

public:
    SeparateChainingTable(int s) : IHashTable(s) {
        table.resize(size);
    }

    void insert(int key) override {
        int idx = getBaseHash(key);
        // Opcjonalnie: jeśli nie chcemy duplikatów, można odkomentować poniższą linię,
        // ale dla czystego O(1) przy wstawianiu po prostu wrzucamy na koniec:
        table[idx].push_back(key);
    }

    bool remove(int key) override {
        int idx = getBaseHash(key);
        auto& chain = table[idx];
        auto it = std::find(chain.begin(), chain.end(), key);
        if (it != chain.end()) {
            chain.erase(it);
            return true;
        }
        return false;
    }

    bool search(int key) override {
        int idx = getBaseHash(key);
        const auto& chain = table[idx];
        return std::find(chain.begin(), chain.end(), key) != chain.end();
    }
};

#endif
#ifndef LINEARPROBINGTABLE_HPP
#define LINEARPROBINGTABLE_HPP

#include "IHashTable.hpp"
#include <vector>

class LinearProbingTable : public IHashTable {
private:
    std::vector<std::string> table;

public:
    LinearProbingTable(int s) : IHashTable(s) {
        table.resize(size, ""); // "" oznacza zupełnie wolne miejsce
    }

    void insert(const std::string& key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size; // Krok o 1: +0, +1, +2...
            if (table[targetIdx] == "" || table[targetIdx] == "<DELETED>") {
                table[targetIdx] = key;
                return;
            }
        }
    }

    bool remove(const std::string& key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size;
            if (table[targetIdx] == "") return false; // Trafiliśmy na puste miejsce -> elementu nie ma
            if (table[targetIdx] == key) {
                table[targetIdx] = "<DELETED>"; // Flaga, żeby nie przerywać wyszukiwania innych kolizji
                return true;
            }
        }
        return false;
    }

    bool search(const std::string& key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size;
            if (table[targetIdx] == "") return false;
            if (table[targetIdx] == key) return true;
        }
        return false;
    }
};

#endif
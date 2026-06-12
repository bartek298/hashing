#ifndef LINEARPROBINGTABLE_HPP
#define LINEARPROBINGTABLE_HPP

#include "IHashTable.hpp"
#include <vector>

class LinearProbingTable : public IHashTable {
private:
    std::vector<int> table;

public:
    LinearProbingTable(int s) : IHashTable(s) {
        table.resize(size, 0); // 0 oznacza wolne miejsce
    }

    void insert(int key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size;
            if (table[targetIdx] == 0 || table[targetIdx] == -1) {
                table[targetIdx] = key;
                return;
            }
        }
    }

    bool remove(int key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size;
            if (table[targetIdx] == 0) return false;
            if (table[targetIdx] == key) {
                table[targetIdx] = -1; // -1 to <DELETED>
                return true;
            }
        }
        return false;
    }

    bool search(int key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i) % size;
            if (table[targetIdx] == 0) return false;
            if (table[targetIdx] == key) return true;
        }
        return false;
    }
};

#endif
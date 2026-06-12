#ifndef QUADRATICPROBINGTABLE_HPP
#define QUADRATICPROBINGTABLE_HPP

#include "IHashTable.hpp"
#include <vector>

class QuadraticProbingTable : public IHashTable {
private:
    std::vector<std::string> table;

public:
    QuadraticProbingTable(int s) : IHashTable(s) {
        table.resize(size, "");
    }

    void insert(const std::string& key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i * i) % size; // Skok kwadratowy: +0, +1, +4, +9...
            if (table[targetIdx] == "" || table[targetIdx] == "<DELETED>") {
                table[targetIdx] = key;
                return;
            }
        }
    }

    bool remove(const std::string& key) override {
        int baseIdx = getBaseHash(key);
        for (int i = 0; i < size; i++) {
            int targetIdx = (baseIdx + i * i) % size;
            if (table[targetIdx] == "") return false;
            if (table[targetIdx] == key) {
                table[table[targetIdx] == key] {
                    table[targetIdx] = "<DELETED>";
                    return true;
                }
            }
            return false;
        }

        bool search(const std::string& key) override {
            int baseIdx = getBaseHash(key);
            for (int i = 0; i < size; i++) {
                int targetIdx = (baseIdx + i * i) % size;
                if (table[targetIdx] == "") return false;
                if (table[targetIdx] == key) return true;
            }
            return false;
        }
    };

#endif
#ifndef IHASHTABLE_HPP
#define IHASHTABLE_HPP

#include <string>
class IHashTable {
protected:
    int size;

    // Wspólna funkcja dla wszystkich metod - wylicza pierwotny indeks
    int getBaseHash(const std::string& key) const {
        unsigned int sum = 0;
        for (char c : key) sum += c;
        return sum % size;
    }

public:
    IHashTable(int s) : size(s) {}
    virtual ~IHashTable() = default;

    // Metody czysto wirtualne, które każda klasa pochodna MUSI zaimplementować
    virtual void insert(const std::string& key) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual bool search(const std::string& key) = 0;
};

#endif
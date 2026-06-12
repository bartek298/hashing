#ifndef IHASHTABLE_HPP
#define IHASHTABLE_HPP

class IHashTable {
protected:
    int size;

public:
    IHashTable(int s) : size(s) {}
    virtual ~IHashTable() {}

    // Funkcja haszująca dla liczb to po prostu modulo
    int getBaseHash(int key) const {
        return (key < 0 ? -key : key) % size;
    }

    virtual void insert(int key) = 0;
    virtual bool remove(int key) = 0;
    virtual bool search(int key) = 0;
};

#endif
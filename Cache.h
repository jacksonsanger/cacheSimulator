#ifndef CACHE_H
#define CACHE_H

#include "Memory.h"
#include "Set.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

class Cache {
private:
    Memory* memory;
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;
    Set** sets; // Array of pointers to Sets
    AddressDecoder* decoder;
    PerformanceCounter* counter;


public:
    // Constructor
    Cache(Memory* memory, int cacheSize, int blockSize, int associativity);

    // Methods to simulate a read and a write
    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);

    // Method to display the cache content
    void display();
};

#endif

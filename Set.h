#ifndef SET_H
#define SET_H

#include "Block.h"
#include "Memory.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"

class Set {
private:
    Block** blocks; // Array of pointers to Blocks
    int associativity;
    int blockSize;
    Memory* memory;
    AddressDecoder* decoder;
    PerformanceCounter* counter;

public:
    // Constructor
    Set(Memory* memory, int associativity, int blockSize, AddressDecoder* decoder, PerformanceCounter* counter);

    // Methods to simulate a read and a write
    unsigned char read(unsigned long address);
    void write(unsigned long address, unsigned char value);

    // Method to display the set content
    void display();

private:
    int findBlock(unsigned long address);
    int findLRUBlock(unsigned long address); //we need to pass the address here so we can get the set index when we evict a block
};

#endif

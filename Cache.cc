#include "Cache.h"
#include <stdio.h>

// Constructor
Cache::Cache(Memory* memory, int cacheSize, int blockSize, int associativity) {
    this->memory = memory;
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->associativity = associativity;
    this->numSets = cacheSize / (blockSize * associativity);

    // Create AddressDecoder and counter instance
    decoder = new AddressDecoder(numSets, blockSize);
    counter = new PerformanceCounter();

    // Create Sets
    sets = new Set*[numSets];
    for (int i = 0; i < numSets; i++) {
        sets[i] = new Set(memory, associativity, blockSize, decoder, counter);
    }
}

// Method to simulate a read
unsigned char Cache::read(unsigned long address) {
    //update the counter
    counter->incrementAccesses();
    //get the set index and then call the read method on the set
    int setIndex = decoder->getSetIndex(address);
    return sets[setIndex]->read(address);
}

// Method to simulate a write
void Cache::write(unsigned long address, unsigned char value) {
    //update the counter
    counter->incrementAccesses();
    //get the set index and then call the write method on the set
    int setIndex = decoder->getSetIndex(address);
    sets[setIndex]->write(address, value);
}

// Method to display the cache content
void Cache::display() {
    printf("CACHE:\n");
    for (int i = 0; i < numSets; i++) {
        printf(" Set %d\n", i);
        sets[i]->display();
    }
    //display the performance results
    counter->display();
}
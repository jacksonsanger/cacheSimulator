#include "Set.h"
#include <stdio.h>

// Constructor
Set::Set(Memory* memory, int associativity, int blockSize, AddressDecoder* decoder, PerformanceCounter* counter) {
    this->memory = memory;
    this->associativity = associativity;
    this->blockSize = blockSize;
    this->decoder = decoder;
    this->counter = counter;

    // Create Blocks
    blocks = new Block*[associativity];
    for (int i = 0; i < associativity; i++) {
        blocks[i] = new Block(blockSize, memory);
    }
}

// Method to simulate a read
unsigned char Set::read(unsigned long address) {
    //first try to find if a matching block is already in the set
    int blockIndex = findBlock(address);
    //if not, we need to evict, or it was empty. Either way this is a miss as we are loading in a new block from main memory
    if (blockIndex == -1) {
        counter->incrementMisses();
        //find the LRU block, we need to pass in the address so we can calculate the set index of the block we will evict
        blockIndex = findLRUBlock(address);
        // get the tag to pass to loadFromMemory and to build the memoryStart location
        unsigned long tag = decoder->getTag(address);
        //get set index to build the memoryStart location
        unsigned long setIndex = decoder->getSetIndex(address);
        // calculate the starting memory address of the block that this address belongs to
        unsigned long memoryStart = decoder->getBlockAddress(tag, setIndex);
        //load the block into the set from memory
        blocks[blockIndex]->loadFromMemory(memoryStart, tag);
    }
    else{
        //if we found the block, it is a hit
        counter->incrementHits();
    }
    //read the block
    return blocks[blockIndex]->read(decoder->getBlockOffset(address));
}

// Method to simulate a write
void Set::write(unsigned long address, unsigned char value) {
    //very similar to the read method above
    int blockIndex = findBlock(address);
    if (blockIndex == -1) {
        counter->incrementMisses();
        blockIndex = findLRUBlock(address); //pass in the address so we can get the set index of the block we will evict
        unsigned long tag = decoder->getTag(address);
        unsigned long setIndex = decoder->getSetIndex(address);
        unsigned long memoryStart = decoder->getBlockAddress(tag, setIndex);
        //load in the block from memory
        blocks[blockIndex]->loadFromMemory(memoryStart, tag);
    }
    else{
        //if we found the block, it is a hit
        counter->incrementHits();
    }
    //modify the value at the offeset (write to the block)
    blocks[blockIndex]->write(decoder->getBlockOffset(address), value);
}

// Method to display the set content
void Set::display() {
    for (int i = 0; i < associativity; i++) {
        printf("  Block %d\n", i);
        blocks[i]->display();
    }
}

// Private method to find a block with the given address
int Set::findBlock(unsigned long address) {
    //loop through all the blocks (the associativity) to try to find a valid matching block
    for (int i = 0; i < associativity; i++) {
        if (blocks[i]->isValid() && blocks[i]->getTag() == decoder->getTag(address)) {
            return i;
        }
    }
    // Block not found, return negative 1
    return -1;
}

// Private method to find the least recently used block
int Set::findLRUBlock(unsigned long address) {
    int lruIndex = 0;
    //initialize the oldest to be the timestamp of the first block
    long oldestTimestamp = blocks[0]->getTimestamp();
    for (int i = 1; i < associativity; i++) {
        //simple min algorithm
        if (blocks[i]->getTimestamp() < oldestTimestamp) {
            lruIndex = i;
            oldestTimestamp = blocks[i]->getTimestamp();
        }
    }
    // If the block is dirty, save it to memory before eviction. this is a writeback
    if (blocks[lruIndex]->isDirty()) {
        counter->incrementWritebacks();
        //we can use the address of the block we were trying to read in to get the set index, as they must be in the same set
        unsigned long evictedSetIndex = decoder->getSetIndex(address);
        unsigned long evictedTag = blocks[lruIndex]->getTag();
        //construct the correct memoryStart location
        unsigned long memoryStart = decoder->getBlockAddress(evictedTag, evictedSetIndex);
        blocks[lruIndex]->saveToMemory(memoryStart);
    }
    return lruIndex;
}

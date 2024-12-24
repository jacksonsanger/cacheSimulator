#include "Block.h"
#include <stdio.h>

// Constructor
Block::Block(int blockSize, Memory* memory) {
    this->blockSize = blockSize;
    this->memory = memory;
    data = new unsigned char[blockSize];
    valid = false;
    dirty = false;
    tag = 0; //default tag value
    timestamp = 0;
}

// Method to read data
unsigned char Block::read(unsigned long offset) {
    //update timestamp
    timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();
    return data[offset];
}

// Method to write data
void Block::write(unsigned long offset, unsigned char value) {
    //set to new value, and mark block as dirt. update timestamp
    data[offset] = value;
    dirty = true;
    timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();
}

// Method to load from memory
void Block::loadFromMemory(unsigned long memoryStart, unsigned long tag) {
    //load "blocksize" blocks from memory by adding i to the starting memory address
    for (int i = 0; i < blockSize; i++) {
        data[i] = memory->getByte(memoryStart + i);
    }
    //block is now valid, and it is not dirty
    valid = true;
    dirty = false;
    //this is where we can assign the tag (why we pass it in)
    this->tag = tag;
}

// Method to save to memory
void Block::saveToMemory(unsigned long memoryStart) {
    //vert similar to above but we are saving to memory
    for (int i = 0; i < blockSize; i++) {
        memory->setByte(memoryStart + i, data[i]);
    }
    //when we save to memory, we are cleaning a dirty block
    dirty = false;
}

// Getter for tag
unsigned long Block::getTag() {
    return tag;
}

// Getter for valid
bool Block::isValid() {
    return valid;
}

// Getter for dirty
bool Block::isDirty() {
    return dirty;
}

// Getter for timestamp
long Block::getTimestamp() {
    return timestamp;
}

// Method to display the block content
void Block::display() {
    printf("    valid: %d    tag: %lu    dirty: %d    timestamp: %ld\n", valid, tag, dirty, timestamp);
    for (int i = 0; i < blockSize; i++) {
        if (i == 0){
            printf("    %02x", data[i]);
        }
        else{
            printf("  %02x", data[i]);
        }

    }
    printf("\n");
}

// Setter for tag
void Block::setTag(unsigned long tag) {
    this->tag = tag;
}

// Setter for valid
void Block::setValid(bool valid) {
    this->valid = valid;
}

// Setter for dirty
void Block::setDirty(bool dirty) {
    this->dirty = dirty;
}

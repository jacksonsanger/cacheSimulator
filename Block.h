#ifndef BLOCK_H
#define BLOCK_H

#include "Memory.h"
#include <chrono>

class Block {
private:
    unsigned char* data; // Array of bytes in the block
    int blockSize;
    unsigned long tag;
    bool valid;
    bool dirty;
    long timestamp;
    Memory* memory;

    std::chrono::high_resolution_clock m_clock;

public:
    // Constructor
    Block(int blockSize, Memory* memory);

    // Methods to read and write data
    unsigned char read(unsigned long offset);
    void write(unsigned long offset, unsigned char value);

    // Methods to load from and save to memory
    void loadFromMemory(unsigned long memoryStart, unsigned long tag);
    void saveToMemory(unsigned long memoryStart);

    // Getter methods
    unsigned long getTag();
    bool isValid();
    bool isDirty();
    long getTimestamp();

    // Method to display the block content
    void display();

    // Setter for tag
    void setTag(unsigned long tag);

    // Setter for valid
    void setValid(bool valid);

    // Setter for dirty
    void setDirty(bool dirty);
};

#endif

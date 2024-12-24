#include "Memory.h"
#include <stdio.h>

// Constructor
Memory::Memory(int size) {
    this->size = size;
    bytes = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        bytes[i] = i % 255;
    }
}

// Getter for memory size
int Memory::getSize() {
    return size;
}

// Method to get a byte at a specific address
unsigned char Memory::getByte(unsigned long address) {
    return bytes[address];
}

// Method to set a byte at a specific address
void Memory::setByte(unsigned long address, unsigned char value) {
        bytes[address] = value;
}

// Method to display the memory content
void Memory::display() {
    printf("MAIN MEMORY:\n");
    for (int i = 0; i < size; i++) {
        printf("%02x ", bytes[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
}

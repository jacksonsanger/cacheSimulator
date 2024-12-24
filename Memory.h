#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    int size;
    unsigned char* bytes;

public:
    // Constructor
    Memory(int size);

    // Getter for memory size
    int getSize();

    // Methods to get and set a byte at a specific address
    unsigned char getByte(unsigned long address);
    void setByte(unsigned long address, unsigned char value);

    // Method to display the memory content
    void display();
};

#endif

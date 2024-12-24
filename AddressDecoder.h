#ifndef ADDRESSDECODER_H
#define ADDRESSDECODER_H

class AddressDecoder {
private:
    int numSets;
    int blockSize;
    int setIndexBits;
    int blockOffsetBits;

public:
    // Constructor
    AddressDecoder(int numSets, int blockSize);

    // Methods to get the tag, set index, and block offset from an address - should these all return unsigned long?
    unsigned long getTag(unsigned long address);
    unsigned long getSetIndex(unsigned long address);
    unsigned long getBlockOffset(unsigned long address);

    // Method to get the starting address of a block in memory
    unsigned long getBlockAddress(unsigned long address, unsigned long setIndex);
};

#endif

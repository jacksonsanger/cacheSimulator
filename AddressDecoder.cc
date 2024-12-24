#include "AddressDecoder.h"
#include <cmath>

// Constructor
AddressDecoder::AddressDecoder(int numSets, int blockSize) {
    this->numSets = numSets;
    this->blockSize = blockSize;
    this->setIndexBits = log2(numSets);
    this->blockOffsetBits = log2(blockSize);
}

// Method to get the tag from an address
unsigned long AddressDecoder::getTag(unsigned long address) {
    return address >> (setIndexBits + blockOffsetBits); //the tag is what is left over after the set index and block offset are removed
}

// Method to get the set index from an address
unsigned long AddressDecoder::getSetIndex(unsigned long address) {
    //first shift 1 left by the set index bits so we will have a number where everything to the right of the 1 is 0 (which is the number of bits)
    unsigned long mask = (1 << setIndexBits);
    //then subtract 1 so that the 1 turns into a 0 and everything to the right of the 1 turns into a 1, effectively creating a mask of the correct number of 1s as the set index bits
    mask = mask - 1;
    //then shift the address right by the block offset bits so that the set index is in the right most position and and with the mask to extract it
    return (address >> blockOffsetBits) & mask;
}

// Method to get the block offset from an address
unsigned long AddressDecoder::getBlockOffset(unsigned long address) {
    //very similar to above, kept in one line for clarity
    unsigned long mask = (1 << blockOffsetBits) - 1;
    //same thing as above but no need to shift the address since block offset is already at the end
    return address & mask;
}

// Method to get the starting address of a block in memory
unsigned long AddressDecoder::getBlockAddress(unsigned long tag, unsigned long setIndex) {
    //move tag all the way to the left, then move set index to be in the "middle", and combine the two
    return (tag << (setIndexBits + blockOffsetBits)) | (setIndex << blockOffsetBits);
}
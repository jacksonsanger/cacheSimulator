#include "PerformanceCounter.h"
#include <stdio.h>

// Constructor
PerformanceCounter::PerformanceCounter() {
    accesses = 0;
    hits = 0;
    misses = 0;
    writebacks = 0;
}

// Methods to update counters
void PerformanceCounter::incrementAccesses() {
    accesses++;
}

void PerformanceCounter::incrementHits() {
    hits++;
}

void PerformanceCounter::incrementMisses() {
    misses++;
}

void PerformanceCounter::incrementWritebacks() {
    writebacks++;
}

// Getter methods
int PerformanceCounter::getAccesses() {
    return accesses;
}

int PerformanceCounter::getHits() {
    return hits;
}

int PerformanceCounter::getMisses() {
    return misses;
}

int PerformanceCounter::getWritebacks() {
    return writebacks;
}

// displau all the info
void PerformanceCounter::display() {
    printf("Accesses:     %d\n", accesses);
    printf("Hits:         %d\n", hits);
    printf("Misses:       %d\n", misses);
    printf("Writebacks:   %d\n", writebacks);
    printf("Miss Perc:    %.2f\n", (misses / (float)accesses) * 100);
    printf("Writeback Perc: %.2f\n", (writebacks / (float)accesses) * 100);
}

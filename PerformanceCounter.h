#ifndef PERFORMANCECOUNTER_H
#define PERFORMANCECOUNTER_H

class PerformanceCounter {
private:
    int accesses;
    int hits;
    int misses;
    int writebacks;

public:
    // Constructor
    PerformanceCounter();

    // Methods to update counters
    void incrementAccesses();
    void incrementHits();
    void incrementMisses();
    void incrementWritebacks();

    // Getter methods
    int getAccesses();
    int getHits();
    int getMisses();
    int getWritebacks();

    // Method to display performance stuff
    void display();
};

#endif

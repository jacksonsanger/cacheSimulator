# Cache Simulation

## Overview
This project implements a flexible and modular cache simulation system. The simulation is designed to model a variety of cache configurations, including direct-mapped, fully associative, and N-way set associative caches. It includes functionality for handling memory reads and writes, cache hits and misses, and eviction policies, with an emphasis on accurate performance tracking.

## Features

### Cache Design
- **Customizable Configurations**:
  - Supports direct-mapped, fully associative, and N-way set associative cache structures.
- **Detailed Memory Address Handling**:
  - Splits memory addresses into Tag, Set Index, and Block Offset for efficient cache access.

### Cache Policies
- **Eviction**: Implements the Least Recently Used (LRU) policy to manage block replacement.
- **Write Policy**:
  - **Write-Allocate**: Loads missing data into the cache on a write miss.
  - **Write-Back**: Updates only the cache on writes and writes back to main memory on eviction if the block is dirty.

### Performance Tracking
- Tracks:
  - Hits
  - Misses
  - Writebacks

### Debugging Tools
- **Memory Dump**: Visualizes the contents of main memory and the cache for easy debugging.
- **Detailed Cache Display**:
  - Outputs the status of each set and block, including validity, tag, dirty flag, and timestamps.

## Classes

### Simulation
- Drives the simulation and orchestrates interactions between the cache and memory.
- Includes test cases to validate the cache behavior under various scenarios.

### Memory
- Models the main memory.
- Provides:
  - `getByte` and `setByte` methods for memory access.
  - A display method for visualizing memory contents.

### Cache
- Manages the cache as an array of sets.
- Provides:
  - `read` and `write` methods for handling memory operations.
  - A display method for debugging.

### Set
- Represents a set in the cache, containing multiple blocks.
- Implements logic for block lookup, replacement, and LRU eviction.

### Block
- Represents a single block/cache line.
- Tracks:
  - Tag
  - Validity
  - Dirty flag
  - Timestamp for LRU management
- Handles loading from and saving to memory.

### AddressDecoder
- Decodes memory addresses into their components:
  - Tag
  - Set Index
  - Block Offset
- Calculates the starting memory address for a block.

### PerformanceCounter
- Tracks performance metrics:
  - Hits
  - Misses
  - Writebacks
- Provides methods to retrieve and display these statistics.

## Technical Details
- **Language**: C++
- **Compilation**: Uses a `Makefile` for incremental compilation.
- **Code Structure**:
  - 7 classes: `Simulation`, `Memory`, `Cache`, `Set`, `Block`, `AddressDecoder`, and `PerformanceCounter`.
  - Separate `.h` and `.cc` files for each class for modularity.

## Key Applications
A simulation tool to understand cache architecture and performance in computing systems.

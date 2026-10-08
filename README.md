# Minimum Spanning Tree (MST) Algorithms Comparison

This repository contains a C implementation and performance comparison of three fundamental algorithms used to find the Minimum Spanning Tree (MST) of a connected, undirected graph. 

This project was developed as part of the "Algorithm Analysis and Design" course (Assignment 3) at the University of Western Macedonia, Dept. of Electrical and Computer Engineering.

## Algorithms Implemented

1. **Prim's Algorithm**: Implemented using an Adjacency List representation.
2. **Kruskal's Algorithm**: Implemented using an Edge List and the Union-Find data structure (with path compression and union by rank).
3. **Reverse-Delete Algorithm**: Implemented by sorting edges in descending order and using Depth-First Search (DFS) to check graph connectivity upon edge removal.

## Project Structure

- `main.c`: Contains the graph generation logic, Prim's algorithm implementation, and execution time measurements.
- `kruskal.h`: Contains the struct definitions and logic for Kruskal's algorithm and Union-Find.
- `reverse_delete.h`: Contains the logic for the Reverse-Delete algorithm and DFS traversal.
- `CMakeLists.txt`: Configuration file for building the project using CMake.
- `Antonis_Tsiggerhs_2026_3.pdf`: The detailed report containing theoretical explanations, step-by-step algorithm tracing on sample graphs, and execution time analysis (in Greek).

## Features

- Dynamic generation of undirected random graphs.
- Customizable graph size (number of vertices).
- Customizable graph sparsity (percentage of edges to remove).
- Execution time measurement and averaging (over 4 runs) for accurate performance comparison.

## Requirements

To build and run this project, you need:
- A C compiler (GCC/MinGW, Clang, etc.) supporting C11 standard.
- CMake (version 3.25 or higher).
- An IDE like CLion (recommended) or a terminal with make/ninja.

## How to Build and Run

### Using CLion
1. Open the repository folder in CLion.
2. CLion will automatically read the `CMakeLists.txt`.
3. Build and Run the project using the IDE's run button.

### Using Terminal (CMake)
Navigate to the project directory and run the following commands:
```bash
mkdir build
cd build
cmake ..
cmake --build .
./test_ergasia3
```

## Usage Example

Upon running, the program will prompt you to enter the graph parameters:
```text
Enter the number of nodes: 150
Enter the percentage of edges to remove: 20
```
The program will then generate the graphs, run all three algorithms, and print the resulting MSTs along with the average execution times for comparison.

## Author
**Antonis Tsiggerhs** - [Team 8]

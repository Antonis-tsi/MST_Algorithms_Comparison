# Minimum Spanning Tree (MST) Algorithms: A Performance Analysis

This repository contains an efficient C implementation and performance comparison of three fundamental Minimum Spanning Tree (MST) algorithms: **Prim's**, **Kruskal's**, and **Reverse-Delete**. 

The goal of this project is to evaluate the execution time and structural approach of each algorithm when applied to randomly generated connected graphs with varying edge densities.

## 🚀 Features

* **Algorithm Implementations:**
  * **Prim's Algorithm:** Implemented using Adjacency Lists and a priority queue logic for optimal space complexity and fast neighbor iteration.
  * **Kruskal's Algorithm:** Implemented using an Edge List and a highly efficient Union-Find (Disjoint Set) data structure with path compression and union by rank.
  * **Reverse-Delete Algorithm:** Implemented by sorting edges in descending order and utilizing Depth First Search (DFS) to dynamically check for graph connectivity.
* **Random Graph Generator:** Generates random graphs with customizable parameters (number of nodes and sparsity/percentage of removed edges) to robustly test the algorithms under different conditions.
* **Performance Profiling:** Built-in CPU time measurement for each algorithm to directly compare their computational efficiency.

## 📊 Performance Benchmark

The algorithms were tested on randomly generated graphs (e.g., 150 nodes with a 20% random edge removal rate). Below is a summary of the average execution times observed during testing:

| Algorithm | Average Execution Time (ms) |
| :--- | :--- |
| **Kruskal** | ~ 0.158 ms |
| **Prim** | ~ 0.164 ms |
| **Reverse-Delete** | ~ 30.545 ms |

### 🔍 Key Observations
* **Prim with Adjacency Lists:** Using an adjacency list instead of an adjacency matrix significantly reduces the space complexity, especially for sparse graphs. It only stores existing edges, avoiding the $V \times V$ memory overhead. Furthermore, iterating over a vertex's neighbors is much faster, as it avoids scanning an entire matrix row/column.
* **Kruskal's Efficiency:** Kruskal's algorithm performs exceptionally well in practice due to the highly optimized Union-Find operations.
* **Reverse-Delete Overhead:** While structurally interesting and a great educational tool for understanding graph cuts, it is predictably the slowest due to the intensive DFS connectivity checks required after every edge deletion.

## 🛠️ Built With
* **Language:** C (Standard C11)
* **Build System:** CMake

## ⚙️ Getting Started

### Prerequisites
* A C compiler (GCC, Clang, etc.)
* CMake (Version 3.25 or higher)

### Build and Run

1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR-USERNAME/Graph-MST-Performance-Analysis.git
   cd Graph-MST-Performance-Analysis
   ```
2. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run the executable:
   ```bash
   ./MST_Algorithms
   ```
   *(Upon execution, you will be prompted to enter the number of nodes and the percentage of edges you wish to randomly remove to create sparsity).*
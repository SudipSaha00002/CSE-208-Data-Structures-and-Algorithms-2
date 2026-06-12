# Data Structures and Algorithms II (DSA-2)

Welcome to the **Data Structures and Algorithms II (CSE 208)** sessional repository. This repository contains C++ implementations of advanced data structures and graph algorithms, written as part of university coursework assignments (Student ID: `2105152`).

Each directory contains specialized algorithms solving classical algorithmic challenges, along with assignment problem statements (PDFs) and sample inputs/outputs.

---

## 📁 Repository Structure

Below is an overview of the modules included in this repository:

| Folder Name | Primary Algorithm / Topic | Description & Core Concepts | Key Files |
| :--- | :--- | :--- | :--- |
| **[`SSSP assignment`](./SSSP%20assignment)** | Single Source Shortest Path | State-space Dijkstra (Cheapest Route with Gas Constraints) & Bellman-Ford (Shortest path modification with range-bounded edge weight additions) | `2105152_Problem1.cpp`, `2105152_Problem2.cpp` |
| **[`APSP assignment`](./APSP%20assignment)** | All Pairs Shortest Path | Floyd-Warshall algorithm for finding threshold-reachable nodes in graphs (City with smallest number of neighbors within distance threshold) | `2105152_Problem1.cpp` |
| **[`MST assignment`](./MST%20assignment)** | Minimum Spanning Trees | Prim's and Kruskal's algorithms (using Disjoint Set Union) for finding and analyzing Minimum Spanning Trees | `2105152_Problem1.cpp` to `Problem3.cpp` |
| **[`Max Flow`](./Max%20Flow)** | Maximum Flow & Matchings | Edmonds-Karp/Ford-Fulkerson max-flow algorithms with applications (e.g., maximum bipartite matching or circulation) | `2105152_problem1.cpp`, `2105152_problem2.cpp` |
| **[`Knapsack`](./Knapsack)** | Knapsack Problems | Classical dynamic programming (0/1 Knapsack) and greedy solutions (Fractional Knapsack) with optimization techniques | `2105152.cpp` |
| **[`Balanced BST`](./Balanced%20BST)** | Red-Black Tree (RBT) | Custom template-based self-balancing Red-Black Tree implementation with insertion, deletion, left/right rotations, recoloring, and search | `2105152_Problem1.cpp`, `color.hpp` |
| **[`HASH TABLE`](./HASH%20TABLE)** | Hash Tables & Probing | Chaining (Linked Lists), Double Hashing, and Custom Probing comparison across different hash functions, load factors, and table sizes | `2105152.cpp` |
| **[`Fibonacci Heap`](./Fibonacci%20Heap)** | Max Fibonacci Heap | High-performance Max-Priority Queue using Fibonacci Heap supporting insertions, extract max, increase key, meld, and deletions | `2105152.cpp` |

---

## 🛠️ Module Descriptions & Algorithms

### 1. Single Source Shortest Path (SSSP)
* **Problem 1 (Gas Constraints Dijkstra):** Modifies Dijkstra's algorithm to solve the gas station shortest path problem. The state space tracks `(city, current_gas)` to find the minimum cost to travel from a source to a destination with tank limit constraints.
* **Problem 2 (Edge Weight Bellman-Ford):** Uses the Bellman-Ford algorithm to check if inserting a new edge $(A, B)$ with a weight within a specified range $[L, H]$ can decrease the shortest path from $S$ to $D$ without introducing negative cycles, returning the optimal weight.

### 2. All Pairs Shortest Path (APSP)
* **Floyd-Warshall:** Solves the all-pairs shortest path problem. The implementation finds the city from which the number of reachable cities within a threshold distance is minimized, resolving ties by choosing the highest indexed city.

### 3. Balanced Binary Search Tree (BST)
* **Red-Black Tree:** A generic template-based `RedBlackTree<Key, Value>` implementation. It supports:
  * Safe insertions and deletions while maintaining RBT invariants (recoloring, parent pointer updates, and rotations).
  * Finding keys, checking if empty, counting total nodes, clearing the tree, and in-order traversals.
  * Interactive CLI console operations: `I` (insert), `E` (erase/delete), `F` (find), `Clr` (clear), `Em` (check empty), `S` (size), and `Itr` (in-order print).

### 4. Hash Table Performance Comparison
* Implements a custom Hash Table supporting:
  * **Collision Resolution:** Chaining (with linked list nodes), Double Hashing, and Custom Probing ($h(k, i) = (h_1(k) + C_1 \cdot i \cdot h_2(k) + C_2 \cdot i^2) \pmod N$).
  * **Hash Functions:** Polynomial rolling hash with different base factors ($37$ and $41$) and XOR bit-mixing.
  * **Rehashing:** Auto-rehashing (doubling table capacity) once the load factor triggers optimization limits.
  * Detailed output logs comparing collision rates and average probe lengths across dynamic input sets (10,000 random words) for various table capacities (5,000, 10,000, and 20,000).

### 5. Max Fibonacci Heap
* Implements a Max Fibonacci Heap for priority queues, featuring:
  * Amortized $O(1)$ insertions, key increases, and heap merging (meld).
  * Amortized $O(\log n)$ extraction of the maximum element (`extract_max`) and arbitrary deletions.
  * Full structure visualization (printing tree node hierarchies).

---

## 🚀 Getting Started & Compiling

To compile and run any of the assignments locally, ensure you have a modern C++ compiler (supporting C++11 or higher, such as `g++`).

### Compilation Example

1. Open your terminal/console.
2. Navigate to the folder of the assignment you wish to run:
   ```bash
   cd "Balanced BST"
   ```
3. Compile the C++ program:
   ```bash
   g++ -std=c++11 2105152_Problem1.cpp -o rbt_program
   ```
4. Run the compiled executable:
   * **Windows:**
     ```bash
     .\rbt_program.exe
     ```
   * **Linux/macOS:**
     ```bash
     ./rbt_program
     ```

*Note: For programs requiring file inputs (like Red-Black Tree or Knapsack), verify that the matching input files (e.g., `input.txt`, `in.txt`) exist in the same directory as the executable.*

---

## 🤝 Contributing & Licensing

This repository contains academic solutions for educational purposes. Feel free to clone and use the code to understand the underlying implementation mechanics of these data structures and algorithms.

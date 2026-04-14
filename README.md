# DSA_Project

# Network Packet Routing Simulator

A C++ project that simulates network packet routing using graph data structures, Dijkstra's shortest path algorithm, and Kruskal's Minimum Spanning Tree (MST) algorithm. Includes a browser-based GUI visualizer.

---

## Features

- **Graph Construction** — Build networks manually or load from file using string-labeled nodes and weighted edges
- **Shortest Path (Dijkstra)** — Find the optimal route between any two nodes with full path reconstruction
- **Packet Simulation** — Simulate packet traversal with or without propagation delay
- **MST (Kruskal)** — Compute minimum spanning tree cost for the network
- **File I/O** — Save/load graphs, log routes, and export MST results
- **GUI Visualizer** — Interactive browser-based graph visualization with Dijkstra path highlighting

---

## Project Structure

    ├── project.h              # Header file — all class and function declarations
    ├── main.cpp               # Entry point, menu-driven CLI
    ├── graph_structure.cpp    # Graph class implementation (adjacency map, edge ops)
    ├── algorithms.cpp         # Dijkstra's and Kruskal's MST implementations
    ├── simulation_layer.cpp   # Packet class and simulation functions
    ├── file_handling.cpp      # Save/load graph, log routes, save MST
    └── gui.html               # Browser-based graph visualizer

---

## Getting Started

### Prerequisites

- C++17 or later
- A C++ compiler (g++, clang++)

### Compilation

    g++ -std=c++17 main.cpp graph_structure.cpp algorithms.cpp simulation_layer.cpp file_handling.cpp -o router

### Run

    ./router

---

## Usage

The CLI presents a menu with the following options:

    1. Enter Graph (nodes and edges)
    2. Load Graph from File
    3. Add Edge
    4. Show Network
    5. Shortest Path (Dijkstra)
    6. Simulate Packet
    7. Simulate Packet with Delay
    8. MST Cost (Kruskal)
    9. Save Graph to File
    10. Exit

### Example Session

    Enter number of nodes: 4
    Enter number of edges: 5
    Enter edges (node1 node2 weight):
    A B 5
    A C 1
    B C 3
    B D 5
    C D 8

    Enter source: A
    Enter destination: D
    Shortest distance: 9
    Path: A -> C -> B -> D

---

## File Formats

### Graph File (save/load)

    5
    A B 5
    A C 1
    B C 3
    B D 5
    C D 8

First line is edge count, followed by `node1 node2 weight` per line.

### routes.txt (auto-generated)

    Route: A -> D
    Path: A -> C -> B -> D
    Cost: 9

### mst.txt (auto-generated)

    MST Cost: 12

---

## GUI Visualizer

Open `gui.html` in any modern browser. The visualizer supports:

- Adding nodes and edges interactively
- Running Dijkstra's algorithm with animated path highlighting
- Viewing edge weights and adjacency list
- Displaying MST cost

---

## Algorithms

### Dijkstra's Shortest Path
- Min-heap priority queue using `std::priority_queue`
- Time complexity: O((V + E) log V)
- Returns distance map and parent map for path reconstruction

### Kruskal's MST
- Edge sorting + Union-Find with path compression and union by rank
- Time complexity: O(E log E)

---

## Team

| Member | Contribution |
|--------|-------------|
| Pavan | `main.cpp`, file handling |
| Dushyant | GUI (`gui.html`), graph structure |
| sauban | Algorithms (Dijkstra, Kruskal) |
| yaswanth] | Simulation layer, packet class |

---

## License

This project was developed as part of a Data Structures and Algorithms course assignment.

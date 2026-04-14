#  DSA Graph Visualizer & Network Simulation

## Overview
This project is a **Data Structures & Algorithms based Graph Simulator and Visualizer** that integrates:

- Core graph algorithms in **C++**
- Backend API using **Python (Flask)**
- Interactive frontend using **HTML + Canvas**

### It allows users to:
- Create and modify graphs  
- Visualize graph structure  
- Run algorithms like:
  - Dijkstra (Shortest Path)
  - Kruskal (Minimum Spanning Tree)  
- Simulate packet transmission in a network  


## Features

### Graph Operations
- Add nodes and edges dynamically  
- Load/save graph from file (`graph.txt`)  
- View graph structure  

### Algorithms Implemented
- **Dijkstra’s Algorithm** for shortest path  
- **Kruskal’s Algorithm** for Minimum Spanning Tree  

### Simulation
- Packet traversal without delay  
- Packet traversal with delay (based on edge weights)  

### Visualization
- Interactive GUI using HTML Canvas  
- Highlights:
  - Shortest path  
  - MST edges  
- Drag-and-drop nodes  

### Backend Integration
- Flask API connects frontend with compiled C++ executable  
- Commands executed via CLI interface in C++  


## Project Structure
- algorithms.cpp (Dijkstra & Kruskal implementation)
- graph_structre.cpp (Graph class implementation)
- simulation_layer.cpp (Packet simulation logic)
- filehandling.cpp (File I/O operations)
- main_function.cpp (CLI + API command handler)
- project.h (Header file)
- server.py (Flask backend server)
- gui.html (Frontend visualization UI)
- graph.txt (Sample graph input)
- README.md (Project documentation)


## How It Works

1. User interacts with the GUI  
2. GUI sends requests to Flask server  
3. Flask calls compiled C++ executable  
4. C++ performs:
   - Graph updates  
   - Algorithm execution  
5. Results are sent back and visualized  


## Algorithms Details

### Dijkstra’s Algorithm
- Uses priority queue  
- Computes shortest distance from source to all nodes  
- Stores parent map for path reconstruction  

###  Kruskal’s Algorithm
- Uses Union-Find (Disjoint Set)  
- Sorts edges by weight  
- Builds MST with minimum cost  



## How to Run

### Step 1: Compile C++ Code
- g++ main_function.cpp algorithms.cpp graph_structre.cpp filehandling.cpp simulation_layer.cpp -o sim.exe
### Step 2: Run Backend Server
- python server.py
### Step 3: Open GUI
- http://localhost:8080

## Functionalities via CLI
### The C++ program supports:
- init → Initialize graph
- addnode <node>
- addedge <a> <b> <w>
- dijkstra <src> <dst>
- mst
- getnodes
- getedges

### (Handled in main_function.cpp)

## Tech Stack
- C++ → Core algorithms
- Python (Flask) → Backend API
- HTML/CSS/JS → Frontend visualization


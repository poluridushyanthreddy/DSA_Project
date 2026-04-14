DSA Graph Visualizer & Network Simulation:

Overview:
This project is a Data Structures & Algorithms based Graph Simulator and Visualizer that integrates:
(i)Core graph algorithms in C++
(ii)Backend API using Python (Flask)
(iii)Interactive frontend using HTML + Canvas

It allows users to:
(i)Create and modify graphs
(ii)Visualize graph structure
(iii)Run algorithms like Dijkstra (Shortest Path) and Kruskal (MST)
(iv)Simulate packet transmission in a network

Features:
(i)Graph Operations
-Add nodes and edges dynamically
-Load/save graph from file (graph.txt)
-View graph structure
(ii)Algorithms Implemented
-Dijkstra’s Algorithm for shortest path
-Kruskal’s Algorithm for Minimum Spanning Tree
(iii)Simulation
-Packet traversal without delay
-Packet traversal with delay (based on edge weights)
(iv)Visualization
-Interactive GUI using HTML Canvas
-Highlights:
Shortest path
MST edges
Drag-and-drop nodes
(v)Backend Integration
-Flask API connects frontend with compiled C++ executable
-Commands executed via CLI interface in C++

Project Structure:
-algorithms.cpp (Dijkstra & Kruskal implementation)
-graph_structre.cpp (Graph class implementation)
-simulation_layer.cpp (Packet simulation logic)
-filehandling.cpp (File I/O operations
-main_function.cpp (CLI + API command handler)
-project.h (Header file (all declarations))
-server.py (Flask backend server)
-gui.html (Frontend visualization UI)
-graph.txt (Sample graph input)
-README.md (Project documentation)

How It Works:
(i)User interacts with the GUI
(ii)GUI sends requests to Flask server
(iii)Flask calls compiled C++ executable
(iv)C++ performs:
-Graph updates
-Algorithm execution
(v)Results sent back and visualized

Algorithms Details:
(i)Dijkstra’s Algorithm
-Uses priority queue
-Computes shortest distance from source to all nodes
-Stores parent map for path reconstruction
(ii)Kruskal’s Algorithm
-Uses Union-Find (Disjoint Set)
-Sorts edges by weight
-Builds MST with minimum cost

Sample Input:
-From graph.txt
9
A B 5
A E 1
A C 1
A F 6
B C 3
B D 5
C E 10
D E 10
F G 3

How to Run:
Step 1: Compile C++ Code-
g++ main_function.cpp algorithms.cpp graph_structre.cpp filehandling.cpp simulation_layer.cpp -o sim.exe
Step 2: Run Backend Server-
python server.py
Step 3: Open GUI-
http://localhost:8080

Functionalities via CLI

The C++ program supports:
init → Initialize graph
addnode <node>
addedge <a> <b> <w>
dijkstra <src> <dst>
mst
getnodes
getedges
-(Handled in main_function.cpp)

Tech Stack:
C++ → Core algorithms
Python (Flask) → Backend API
HTML/CSS/JS → Frontend visualization
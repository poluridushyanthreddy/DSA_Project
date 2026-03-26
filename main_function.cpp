#include <iostream>
#include <vector>
#include "graph.h"
#include "dijkstra.h"
#include "kruskal.h"
#include "packet.h"

using namespace std;


void loadFromFile(Graph &g, string filename);

int main() {
    Graph g;

    
    loadFromFile(g, "edges.txt");

    cout << "\nGraph Loaded:\n";
    g.printGraph();

    // 🔹 Run Dijkstra
    string source = "A";
    string dest = "D";

    cout << "\nRunning Dijkstra...\n";
    vector<string> path = dijkstra(g, source, dest);

    cout << "Shortest Path: ";
    for (auto node : path) {
        cout << node << " ";
    }
    cout << endl;

    // 🔹 Run Kruskal
    cout << "\nRunning Kruskal...\n";
    kruskal(g);

    // 🔹 Packet Simulation
    Packet p(source, dest);   

    cout << "\nSimulating Packet:\n";
    simulatePacket(p);

    return 0;
}

#ifndef PROJECT_H
#define PROJECT_H
#include <bits/stdc++.h>

using namespace std;

// -------- GRAPH --------

class graph {
public:
    int n, m;
    map<string, vector<pair<string,int>>> grh;
    graph(int n, int m);
    void addedge(string a, string b, int c);
    void fill();
    void print();
    int getWeight(string u, string v);
    vector<pair<string,int>> getNeighbours(string node);
    vector<string> getNodes();
    vector<tuple<string,string,int>> getAllEdges();
};

// -------- DIJKSTRA --------

map<string,int> dijkstra(graph &g, string src, map<string,string> &parent);
void printPath(string dest, map<string,string> &parent);

// -------- MST --------

int kruskalMST(graph &g);

// -------- PACKET --------

class packet {
public:
    char source;
    char destination;
    char current_node;
    vector<char> path;
    int total_time;
    bool delivered;
    packet(char s, char d);
};

// -------- SIMULATION --------

void simulatepacket(packet &p);
void simulatepacketwithdelay(packet &p, graph &g);

#endif
void simulatepacket(packet &p);
void simulatepacketwithdelay(packet &p, graph &g);

#endif

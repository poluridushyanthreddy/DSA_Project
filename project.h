#ifndef PROJECT_H
#define PROJECT_H

#include <bits/stdc++.h>
using namespace std;

// -------- GRAPH --------
class graph {
public:
    int n, m;
    vector<vector<pair<char,int>>> grh;

    graph(int n, int m);
    void addedge(char a, char b, int c);
    void fill();
    void print();
    int getWeight(char u, char v);
};

// -------- DIJKSTRA --------
map<char,int> dijkstra(graph &g, char src, map<char,char> &parent);

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
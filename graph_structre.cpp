#include "project.h"
#include <iostream>
using namespace std;

// getWeight
int graph::getWeight(char u, char v) {
    for(auto &edge : grh[u - 'A']) {
        if(edge.first == v)
            return edge.second;
    }
    return INT_MAX;
}
graph::graph(int n, int m) {
    this->n = n;
    this->m = m;
    grh.resize(n);
}
// print
void graph::print() {
    for(int i = 0; i < n; i++) {
        char node = char(i + 'A');
        cout << node << " -> ";

        for(auto &edge : grh[i]) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }

        cout << endl;
    }
}

// addedge
void graph::addedge(char a, char b, int c) {
    int u = a - 'A';
    int v = b - 'A';

    grh[u].push_back({b, c});
    grh[v].push_back({a, c});
}

// fill
void graph::fill() {
    for(int i = 0; i < m; i++) {
        char a, b;
        int c;
        cin >> a >> b >> c;
        addedge(a, b, c);  // reuse function
    }
}
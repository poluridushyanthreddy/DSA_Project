#include <bits/stdc++.h>
using namespace std;

// ======================= DIJKSTRA =======================

// Returns shortest distances from source
map<string, int> dijkstra(Graph &g, string source, map<string, string> &parent) {
    map<string, int> dist;

    // Initialize distances
    for (auto node : g.adj) {
        dist[node.first] = INT_MAX;
    }

    // Min heap: (distance, node)
    priority_queue<pair<int, string>, 
        vector<pair<int, string>>, 
        greater<pair<int, string>>> pq;

    dist[source] = 0;
    pq.push({0, source});
    parent[source] = "";

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int currDist = top.first;
        string node = top.second;

        for (auto neighbor : g.adj[node]) {
            string nextNode = neighbor.first;
            int weight = neighbor.second;

            if (currDist + weight < dist[nextNode]) {
                dist[nextNode] = currDist + weight;
                pq.push({dist[nextNode], nextNode});
                parent[nextNode] = node;
            }
        }
    }

    return dist;
}

// Function to print shortest path
void printPath(string dest, map<string, string> &parent) {
    if (dest == "") return;
    printPath(parent[dest], parent);
    cout << dest << " ";
}

// ======================= UNION-FIND =======================

map<string, string> parentUF;

string findSet(string x) {
    if (parentUF[x] != x)
        parentUF[x] = findSet(parentUF[x]);
    return parentUF[x];
}

void unionSet(string a, string b) {
    parentUF[findSet(a)] = findSet(b);
}

// ======================= KRUSKAL =======================

int kruskalMST(Graph &g) {
    vector<tuple<int, string, string>> edges;

    // Build edge list (avoid duplicates)
    for (auto u : g.adj) {
        for (auto v : u.second) {
            if (u.first < v.first) {  // avoid double edges
                edges.push_back({v.second, u.first, v.first});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    // Initialize Union-Find
    for (auto node : g.adj) {
        parentUF[node.first] = node.first;
    }

    int mstCost = 0;

    cout << "\nMST Edges:\n";

    for (auto edge : edges) {
        int weight;
        string u, v;
        tie(weight, u, v) = edge;

        if (findSet(u) != findSet(v)) {
            unionSet(u, v);
            mstCost += weight;
            cout << u << " - " << v << " : " << weight << endl;
        }
    }

    return mstCost;
}
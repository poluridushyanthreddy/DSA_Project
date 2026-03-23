#include "algorithms.h"
#include "graph.h"
#include <queue>
#include <algorithm>

map<string,int> dijkstraShortestPath(Graph &g, string source, map<string,string> &parent) {
    map<string,int> dist;

    for(auto &node : g.adj)
        dist[node.first] = INT_MAX;

    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;

    dist[source] = 0;
    parent[source] = "";
    pq.push({0, source});

    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int currDist = top.first;
        string currNode = top.second;

        if(currDist > dist[currNode]) continue;

        for(auto &nbr : g.adj[currNode]) {
            string next = nbr.first;
            int w = nbr.second;

            if(currDist + w < dist[next]) {
                dist[next] = currDist + w;
                parent[next] = currNode;
                pq.push({dist[next], next});
            }
        }
    }

    return dist;
}

void printPath(string dest, map<string,string> &parent) {
    if(dest == "") return;
    printPath(parent[dest], parent);
    cout << dest << " ";
}

int kruskalMST(Graph &g) {
    vector<tuple<int,string,string>> edges;

    for(auto &u : g.adj) {
        for(auto &v : u.second) {
            if(u.first < v.first)
                edges.push_back({v.second, u.first, v.first});
        }
    }

    sort(edges.begin(), edges.end());

    map<string,string> parent;
    map<string,int> rank;

    for(auto &node : g.adj) {
        parent[node.first] = node.first;
        rank[node.first] = 0;
    }

    function<string(string)> findSet = [&](string x) {
        if(parent[x] != x)
            parent[x] = findSet(parent[x]);
        return parent[x];
    };

    function<void(string,string)> unionSet = [&](string a, string b) {
        string pa = findSet(a);
        string pb = findSet(b);

        if(pa == pb) return;

        if(rank[pa] < rank[pb]) parent[pa] = pb;
        else if(rank[pa] > rank[pb]) parent[pb] = pa;
        else {
            parent[pb] = pa;
            rank[pa]++;
        }
    };

    int totalCost = 0;

    cout << "\nMST Edges:\n";

    for(auto &e : edges) {
        int w;
        string u, v;
        tie(w, u, v) = e;

        if(findSet(u) != findSet(v)) {
            unionSet(u, v);
            totalCost += w;
            cout << u << " - " << v << " : " << w << endl;
        }
    }

    return totalCost;
}
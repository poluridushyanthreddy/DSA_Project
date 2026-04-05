#include "project.h"
#include <bits/stdc++.h>
using namespace std;

map<string,int> dijkstra(graph &g, string src, map<string,string> &parent)
{
    map<string,int> distance;

    for(auto node : g.getNodes())
    {
        distance[node] = INT_MAX;
    }

    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;

    distance[src] = 0;
    parent[src] = "";
    pq.push({0, src});

    while(!pq.empty())
    {
        pair<int,string> current = pq.top();
        pq.pop();

        int currDist = current.first;
        string node = current.second;

        if(currDist > distance[node])
            continue;

        for(auto edge : g.getNeighbours(node))
        {
            string nextNode = edge.first;
            int weight = edge.second;

            int newDist = currDist + weight;

            if(newDist < distance[nextNode])
            {
                distance[nextNode] = newDist;
                parent[nextNode] = node;
                pq.push({newDist, nextNode});
            }
        }
    }

    return distance;
}

void printPath(string dest, map<string,string> &parent)
{
    if(dest == "")
        return;

    printPath(parent[dest], parent);
    cout << dest << " ";
}

int kruskalMST(graph &g)
{
    vector<tuple<int,string,string>> edges;

    for(auto e : g.getAllEdges())
    {
        string u, v;
        int w;
        tie(u, v, w) = e;

        edges.push_back({w, u, v});
    }

    sort(edges.begin(), edges.end());

    map<string,string> parent;
    map<string,int> rank;

    for(auto node : g.getNodes())
    {
        parent[node] = node;
        rank[node] = 0;
    }

    function<string(string)> findSet = [&](string x)
    {
        if(parent[x] != x)
            parent[x] = findSet(parent[x]);
        return parent[x];
    };

    function<void(string,string)> unionSet = [&](string a, string b)
    {
        string pa = findSet(a);
        string pb = findSet(b);

        if(pa == pb)
            return;

        if(rank[pa] < rank[pb])
            parent[pa] = pb;
        else if(rank[pa] > rank[pb])
            parent[pb] = pa;
        else
        {
            parent[pb] = pa;
            rank[pa]++;
        }
    };

    int totalCost = 0;

    for(auto e : edges)
    {
        int w;
        string u, v;
        tie(w, u, v) = e;

        if(findSet(u) != findSet(v))
        {
            unionSet(u, v);
            totalCost += w;
        }
    }

    return totalCost;
}
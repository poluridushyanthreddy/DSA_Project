#include "project.h"
#include <iostream>
using namespace std;

// getWeight
int graph::getWeight(string u, string v) {
    for(auto &edge : grh[u]) {
        if(edge.first == v) return edge.second;
    }
    return INT_MAX;
}
graph::graph(int n, int m) {
    this->n = n;
    this->m = m;
}
vector<pair<string,int>> graph::getNeighbours(string Node)
{
    return grh[Node];
} 
vector<string> graph::getNodes()
{
    vector<string> nodes;
    for(auto &edge:grh)
    {
        nodes.push_back(edge.first);
    }
    return nodes;
}

vector<tuple<string,string,int>> graph::getAllEdges()
{
    vector<tuple<string,string,int>> edges;
    for(auto &edge:grh)
    {
        string u = edge.first;
        for(auto e:edge.second)
        {
            string v = e.first;
            int w = e.second;
            if(u<v)
            edges.push_back({u,v,w});
        }
    }
    return edges;
}

void graph::print() {
    for(auto &edge:grh)
    {
        cout<<"Node ->"<<edge.first;
        for(auto e:edge.second)
        {
            cout<<" ("<<e.first<<" , "<<e.second<<") ";
        }
        cout<<endl;
}
}
// addedge
void graph::addedge(string a, string  b, int c) {
    grh[a].push_back({b, c});
    grh[b].push_back({a, c});
}
// fill
void graph::fill() {
    for(int i=0; i<m; i++) {
        string a,b;
        int c;
        cin>>a>>b>>c;
        addedge(a,b,c);
    }
}
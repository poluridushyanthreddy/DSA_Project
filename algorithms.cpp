#include "project.h"


map<char,int> dijkstra(graph &g, char src, map<char,char> &parent)
{
    map<char,int> distance;

    for(int i=0;i<g.n;i++)
    {
        char node=char(i + 65);
        distance[node]=INT_MAX;
    }

    priority_queue<pair<int,char>,vector<pair<int,char>>,greater<pair<int,char>>>pq;

    distance[src]=0;
    parent[src]='\0';
    pq.push({0, src});

    while(!pq.empty())
    {
        pair<int,char> current=pq.top();
        pq.pop();

        int currDist=current.first;
        char node=current.second;

        if(currDist > distance[node])
            continue;

        for(auto edge : g.grh[node - 65])
        {
            char nextNode=edge.first;
            int weight=edge.second;

            int newDist=currDist + weight;

            if(newDist < distance[nextNode])
            {
                distance[nextNode]=newDist;
                parent[nextNode]=node;
                pq.push({newDist,nextNode});
            }
        }
    }

    return distance;
}
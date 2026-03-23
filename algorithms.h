#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Graph;

map<string,int> dijkstraShortestPath(Graph &g,string source,map<string,string> &parent);

void printPath(string dest,map<string, string> &parent);

int kruskalMST(Graph &g);

#endif
#include "project.h"
 
void saveGraphToFile(graph &g, string filename)
{
    ofstream fout(filename);
    if(!fout)
    {
        cout << "Error opening file!\n";
        return;
    }
    auto edges = g.getAllEdges();
    fout << edges.size() << "\n";
    for(auto e : edges)
    {
        string u, v;
        int w;
        tie(u, v, w) = e;
        fout << u << " " << v << " " << w << "\n";
    }
    fout.close();
    cout << "Graph saved to " << filename << "\n";
}
 
graph loadGraphFromFile(string filename)
{
    ifstream fin(filename);
    if(!fin)
    {
        cout << "Error opening file!\n";
        return graph(0, 0);
    }
    int m;
    fin >> m;
    graph g(0, m);
    for(int i = 0; i < m; i++)
    {
        string a, b;
        int c;
        fin >> a >> b >> c;
        g.addedge(a, b, c);
    }
    fin.close();
    cout << "Graph loaded from " << filename << "\n";
    return g;
}
 
void logRouteToFile(string filename, string src, string dest, vector<string> path, int cost)
{
    ofstream fout(filename, ios::app);
    if(!fout)
    {
        cout << "Error opening file!\n";
        return;
    }
    fout << "Route: " << src << " -> " << dest << "\n";
    fout << "Path: ";
    for(int i = 0; i < path.size(); i++)
    {
        fout << path[i];
        if(i + 1 < path.size())
            fout << " -> ";
    }
    fout << "\nCost: " << cost << "\n\n";
    fout.close();
    cout << "Route saved to " << filename << "\n";
}
 
void saveMSTToFile(string filename, int cost)
{
    ofstream fout(filename, ios::app);
    if(!fout)
    {
        cout << "Error opening file!\n";
        return;
    }
    fout << "MST Cost: " << cost << "\n";
    fout.close();
    cout << "MST saved to " << filename << "\n";
}

#include "project.h"
#include "filehandling.cpp"
#include <bits/stdc++.h>
using namespace std;
 
vector<string> buildPath(string src, string dest, map<string,string> &parent)
{
    vector<string> path;
    string cur = dest;
    while(cur != "")
    {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}
 
int main()
{
    graph g(0, 0);
 
    int choice;
    do
    {

        cout << "1. Enter Graph (nodes and edges)\n";
        cout << "2. Load Graph from File\n";
        cout << "3. Add Edge\n";
        cout << "4. Show Network\n";
        cout << "5. Shortest Path (Dijkstra)\n";
        cout << "6. Simulate Packet\n";
        cout << "7. Simulate Packet with Delay\n";
        cout << "8. MST Cost (Kruskal)\n";
        cout << "9. Save Graph to File\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
 
        if(choice == 1)
        {
            int n, m;
            cout << "Enter number of nodes: ";
            cin >> n;
            cout << "Enter number of edges: ";
            cin >> m;
            g = graph(n, m);
            cout << "Enter edges (node1 node2 weight):\n";
            g.fill();
        }
        else if(choice == 2)
        {
            string fname;
            cout << "Enter filename: ";
            getline(cin, fname);
            g = loadGraphFromFile(fname);
        }
        else if(choice == 3)
        {
            string a, b;
            int w;
            cout << "Enter node1 node2 weight: ";
            cin >> a >> b >> w;
            g.addedge(a, b, w);
            cout << "Edge added!\n";
        }
        else if(choice == 4)
        {
            g.print();
        }
        else if(choice == 5)
        {
            string src, dest;
            cout << "Enter source: ";
            cin >> src;
            cout << "Enter destination: ";
            cin >> dest;
 
            map<string,string> parent;
            map<string,int> dist = dijkstra(g, src, parent);
 
            if(dist[dest] == INT_MAX)
            {
                cout << "No path found!\n";
            }
            else
            {
                cout << "Shortest distance: " << dist[dest] << "\n";
                cout << "Path: ";
                printPath(dest, parent);
                cout << "\n";
 
                vector<string> path = buildPath(src, dest, parent);
                logRouteToFile("routes.txt", src, dest, path, dist[dest]);
            }
        }
        else if(choice == 6)
        {
            string src, dest;
            cout << "Enter source: ";
            cin >> src;
            cout << "Enter destination: ";
            cin >> dest;
 
            map<string,string> parent;
            map<string,int> dist = dijkstra(g, src, parent);
 
            if(dist[dest] == INT_MAX)
            {
                cout << "No path found!\n";
            }
            else
            {
                vector<string> path = buildPath(src, dest, parent);
                packet p(src[0], dest[0]);
                for(auto node : path)
                    p.path.push_back(node[0]);
                simulatepacket(p);
            }
        }
        else if(choice == 7)
        {
            string src, dest;
            cout << "Enter source: ";
            cin >> src;
            cout << "Enter destination: ";
            cin >> dest;
 
            map<string,string> parent;
            map<string,int> dist = dijkstra(g, src, parent);
 
            if(dist[dest] == INT_MAX)
            {
                cout << "No path found!\n";
            }
            else
            {
                vector<string> path = buildPath(src, dest, parent);
                packet p(src[0], dest[0]);
                for(auto node : path)
                    p.path.push_back(node[0]);
                simulatepacketwithdelay(p, g);
            }
        }
        else if(choice == 8)
        {
            int cost = kruskalMST(g);
            cout << "MST cost: " << cost << "\n";
            saveMSTToFile("mst.txt", cost);
        }
        else if(choice == 9)
        {
            string fname;
            cout << "Enter filename: ";
            getline(cin, fname);
            saveGraphToFile(g, fname);
        }
        else if(choice == 10)
        {
            cout << "Bye!\n";
        }
        else
        {
            cout << "Invalid choice\n";
        }
 
    } while(choice != 10);
 
    return 0;
}

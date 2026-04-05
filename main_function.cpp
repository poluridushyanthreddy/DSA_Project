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
    int n, m;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;
 
    graph g(n, m);
    cout << "Enter edges (node1 node2 weight):\n";
    g.fill();
 
    int choice;
    do
    {
        cout << "1. Add Edge\n";
        cout << "2. Show Network\n";
        cout << "3. Shortest Path (Dijkstra)\n";
        cout << "4. Simulate Packet\n";
        cout << "5. Simulate Packet with Delay\n";
        cout << "6. MST Cost (Kruskal)\n";
        cout << "7. Save Graph to File\n";
        cout << "8. Load Graph from File\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
 
        if(choice == 1)
        {
            string a, b;
            int w;
            cout << "Enter node1 node2 weight: ";
            cin >> a >> b >> w;
            g.addedge(a, b, w);
            cout << "Edge added!\n";
        }
        else if(choice == 2)
        {
            g.print();
        }
        else if(choice == 3)
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
        else if(choice == 4)
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
                vector<string> path = buildPath(src, dest, parent);
                packet p(src[0], dest[0]);
                for(auto node : path)
                    p.path.push_back(node[0]);
                simulatepacketwithdelay(p, g);
            }
        }
        else if(choice == 6)
        {
            int cost = kruskalMST(g);
            cout << "MST cost: " << cost << "\n";
            saveMSTToFile("mst.txt", cost);
        }
        else if(choice == 7)
        {
            string fname;
            cout << "Enter filename: ";
            getline(cin, fname);
            saveGraphToFile(g, fname);
        }
        else if(choice == 8)
        {
            string fname;
            cout << "Enter filename: ";
            getline(cin, fname);
            g = loadGraphFromFile(fname);
        }
        else if(choice == 9)
        {
            cout << "Bye!\n";
        }
        else
        {
            cout << "Invalid choice\n";
        }
 
    } while(choice != 9);
 
    return 0;
}

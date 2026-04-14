#include "project.h"

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

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        string cmd = argv[1];

        // init must come first — graph.txt may not exist yet
        if(cmd == "init")
        {
            graph empty(0, 0);
            saveGraphToFile(empty, "graph.txt");
            cout << "ok" << endl;
            return 0;
        }

        // all other commands load graph.txt first
        graph g = loadGraphFromFile("graph.txt");

        if(cmd == "addnode" && argc == 3)
        {
            string a = argv[2];
            g.addnode(a);
            saveGraphToFile(g, "graph.txt");
            cout << "ok" << endl;
        }
        else if(cmd == "addedge" && argc == 5)
        {
            string a = argv[2];
            string b = argv[3];
            int w = stoi(argv[4]);
            g.addedge(a, b, w);
            saveGraphToFile(g, "graph.txt");
            cout << "ok" << endl;
        }
        else if(cmd == "dijkstra" && argc == 4)
        {
            string src = argv[2];
            string dst = argv[3];
            map<string,string> parent;
            map<string,int> dist = dijkstra(g, src, parent);
            if(dist[dst] == INT_MAX)
            {
                cout << "nopath" << endl;
            }
            else
            {
                vector<string> path = buildPath(src, dst, parent);
                for(int i = 0; i < (int)path.size(); i++)
                {
                    cout << path[i];
                    if(i + 1 < (int)path.size()) cout << ",";
                }
                cout << " " << dist[dst] << endl;
            }
        }
        else if(cmd == "mst")
        {
            vector<tuple<int,string,string>> sortedEdges;
            for(auto e : g.getAllEdges())
            {
                string u, v; int w;
                tie(u, v, w) = e;
                sortedEdges.push_back({w, u, v});
            }
            sort(sortedEdges.begin(), sortedEdges.end());

            map<string,string> par;
            map<string,int> rnk;
            for(auto n : g.getNodes())
            {
                par[n] = n;
                rnk[n] = 0;
            }

            function<string(string)> find = [&](string x) -> string
            {
                if(par[x] != x) par[x] = find(par[x]);
                return par[x];
            };

            function<bool(string,string)> unite = [&](string a, string b) -> bool
            {
                string pa = find(a), pb = find(b);
                if(pa == pb) return false;
                if(rnk[pa] < rnk[pb]) par[pa] = pb;
                else if(rnk[pa] > rnk[pb]) par[pb] = pa;
                else { par[pb] = pa; rnk[pa]++; }
                return true;
            };

            int cost = 0;
            string edgeOut = "";
            for(auto &e : sortedEdges)
            {
                int w; string u, v;
                tie(w, u, v) = e;
                if(unite(u, v))
                {
                    cost += w;
                    edgeOut += u + " " + v + ",";
                }
            }
            cout << cost << endl;
            cout << edgeOut << endl;
        }
        else if(cmd == "getnodes")
        {
            for(auto n : g.getNodes())
                cout << n << ",";
            cout << endl;
        }
        else if(cmd == "getedges")
        {
            for(auto e : g.getAllEdges())
            {
                string u, v; int w;
                tie(u, v, w) = e;
                cout << u << " " << v << " " << w << ",";
            }
            cout << endl;
        }
        else
        {
            cout << "unknown command" << endl;
        }

        return 0;
    }

    // ── YOUR ORIGINAL MENU BELOW — UNTOUCHED ──

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
                packet p(src, dest);
                for(auto node : path)
                    p.path.push_back(node);
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
                packet p(src, dest);
                for(auto node : path)
                    p.path.push_back(node);
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
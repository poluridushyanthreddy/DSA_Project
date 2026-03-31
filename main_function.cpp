#include "project.h"
int main() {
    int n, m;
    cout << "Enter number of nodes and edges:\n";
    cin >> n >> m;

    graph g(n, m);

    cout << "Enter edges (format: A B weight):\n";
    g.fill();

    cout << "\nGraph:\n";
    g.print();

    char src, dest;
    cout << "\nEnter source and destination:\n";
    cin >> src >> dest;

    // Dijkstra
    map<char, char> parent;
    map<char, int> dist = dijkstra(g, src, parent);

    // Check if reachable
    if(dist[dest] == INT_MAX) {
        cout << "No path exists\n";
        return 0;
    }

    // Reconstruct path
    vector<char> path;
    char cur = dest;

    while(cur != '\0') {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    // Print path
    cout << "\nShortest Path: ";
    for(char c : path) cout << c << " ";
    cout << "\nCost: " << dist[dest] << endl;

    // Packet simulation
    packet p(src, dest);
    p.path = path;

    simulatepacket(p);

    // reset packet state for delay simulation
    p.current_node = src;
    p.total_time = 0;
    p.delivered = false;

    simulatepacketwithdelay(p, g);

    return 0;
}
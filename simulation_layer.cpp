#include "project.h"

void simulatepacket(packet &p) {
    cout << "\n-- Simulation without delay --\n";

    for(string node : p.path) {
        p.current_node = node;
        cout << "Packet at node: " << node << endl;
    }

    p.delivered = true;
    cout << "Packet delivered to destination: " << p.destination << endl;
}

packet::packet(string s, string d) {
    source = s;
    destination = d;
    current_node = s;
    total_time = 0;
    delivered = false;
}

void simulatepacketwithdelay(packet &p, graph &g) {
    cout << "\n-- Simulation with delay --\n";

    for(int i = 0; i < p.path.size() - 1; i++) {
        string u = p.path[i];
        string v = p.path[i + 1];

        int delay = g.getWeight(u, v);

        cout << "Moving " << u << " -> " << v
             << " | Delay: " << delay << endl;

        p.current_node = v;
        p.total_time += delay;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    p.delivered = true;

    cout << "Packet delivered\n";
    cout << "Total time taken: " << p.total_time << endl;
}

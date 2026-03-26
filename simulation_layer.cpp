#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<chrono>
#include<thread>

using namespace std;

class packet{
    public :
    int source;
    int destination;
    int current_node;
    vector<int>path;
    int total_time;
    bool delivered;

    packet(int s,int d){
        source = s;
        destination = d;
        current_node = s;
        total_time = 0;
        delivered = false;
    }
};

void simulatepacket(packet &p){
    cout<<"\n -- Simulation without dealy -- \n";

    for(int node : p.path){
        p.current_node = node;
        cout<<"Packet at node : "<<node<<endl;
    }

    p.delivered = true;
    cout<<"Packet delivered to destination : "<<p.destination<<endl;
}

void simulatepacketwithdelay(packet &p, graph &g){  //add the graph to get the delay between nodes
    cout<<"\n--- Simulation with delay of---\n";

   for(int i=0;i<p.path.size();i++){
    int u = p.path[i];
    int v = p.path[i+1];

    int delay = g.getWeight(u,v);

    cout<<"Moving"<< u << "->"<< v 
        <<"Delay : "<< delay<< endl;

    p.current_node = v;
    p.total_time += delay;
    
    // this_thread::sleep_for(chrono::milliseconds(500));
   }

   p.delivered = true;

   cout<<"Packet delivered " << "\n";
   cout<<"Total time taken : "<< p.total_time << "\n";
}

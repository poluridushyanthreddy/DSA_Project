#include <bits/stdc++.h>
using namespace std;

class graph
{
    public:

    int n,m;
    vector<vector<pair<int,int>>> grh;
    graph(int n,int m)
    {
        this->n=n;
        this->m=m;
        grh.resize(n);
    }
    void fill()
    {
        for(int i=0;i<m;i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            grh[a].push_back({b, c}); 
            grh[b].push_back({a, c});
        }
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    graph g(n,m);
    g.fill();
    for(int i = 0; i < n; i++) {
        cout << "Node " << i << ": ";
        for(auto &edge : g.grh[i]) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << "\n";
    }
return 0;
}
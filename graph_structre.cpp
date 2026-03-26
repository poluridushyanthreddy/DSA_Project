#include <bits/stdc++.h>
using namespace std;

class graph
{
    public:

    int n,m;
    vector<vector<pair<char,int>>> grh;
    graph(int n,int m)
    {
        this->n=n;
        this->m=m;
        grh.resize(n);
    }

    void addrouter()
    {
        grh.resize(grh.size()+1);
    }

    void addedge(char a,char b,int c)
    {
        grh[a-65].push_back({b,c});
        grh[b-65].push_back({a,c});
    }
    void fill()
    {
        for(int i=0;i<m;i++)
        {
            char a,b;int c;
            cin>>a>>b>>c;
            grh[a-65].push_back({b, c}); 
            grh[b-65].push_back({a, c});
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
        cout << "Node " << char(i+65) << ": ";
        for(auto &edge : g.grh[i]) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << "\n";
    }
return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define ADD 1000005

map<int, map<int,int>> gr;

int main()
{
    int N; cin>>N;

    int maxvalue=0;
    
    for(int i=0; i<N; i++)
    {
        int a, b; cin>>a>>b;
        gr[a][b+ADD] = 1;
        gr[b+ADD][a] = 0;
        maxvalue = max(maxvalue, b+ADD);
     }

    int s = maxvalue+5, t = maxvalue+6;

    for(auto it:gr)
    {
        if(it.second.size() %3)
        {
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes\n";
   
    for(auto it:gr)
    {
        if(it.first<ADD)
            gr[s][it.first] = it.second.size()/3;
        else if(it.first<=maxvalue)
            gr[it.first][t] = it.second.size()/3;
    }

    int flow = 0;   

    while(true)
    {
        map<int, int> prv;
        map<int, bool> visited;

        stack<pair<int,int>> st;
        st.push({s, -1});
        while(!st.empty())
        {
            auto [nd, p] = st.top();
            st.pop();
            visited[nd] = 1;
            prv[nd] = p;
            if(nd == t) break;

            for(auto [u, b] : gr[nd])
                    if(b && !visited[u])
                        st.push({u, nd});
        }

        if(!visited[t]) break;
        
        flow++;
        int nd = t;

        while(nd!=s)
        {
            gr[nd][prv[nd]] +=  1;
            gr[prv[nd]][nd] -= 1;
            nd = prv[nd];
        }
    }
    
    cout<<flow<<endl;

    for(auto [nd, adj]:gr)
    {
        if(nd == s || nd == t || nd<ADD) continue;

        for(auto [u, b] : adj)
            if(u!=t && b)
                cout<<u<<" "<<nd-ADD<<endl;
    }
}

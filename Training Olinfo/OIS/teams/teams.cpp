#include<bits/stdc++.h>
using namespace std;

int N;
vector<map<int ,int>> gr;
vector<vector<int>> c;
vector<int> d, dp; //days of meetings
vector<bool> visited;
vector<int> prv;
int s, t;

int spfa()
{
    fill(prv.begin(), prv.end(), -1);
    fill(visited.begin(), visited.end(), 0);
    fill(dp.begin(), dp.end(), -1);
    
    dp[s] = 0;
    queue<int> q;
    q.push(s);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        visited[v] = 0;
        
        for(auto [u, w] : gr[v])
        {
            if(!w) continue;

            if(dp[u] <  dp[v] + c[v][u])
            {
                if(!visited[u])
                    q.push(u);
                dp[u] = dp[v] + c[v][u];
                prv[u] = v;
                visited[u] = 1;
            }
        }
    }
    return dp[t];
}

int main()
{
    cin>>N;
    prv.resize(N*2+3);
    visited.resize(N*2+3);
    gr.resize(N*2+3);
    d.resize(N);
    dp.resize(N*2+3);
    c.resize(N*2+3, vector<int> (N*2+3));

    s = N*2+1; t = N*2+2;
    
    for(auto &i:d) cin>>i;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int b; cin>>b;
            
            if(d[i]+b<=d[j])
                gr[i*2+1][j*2] = 1;
        }
    }

    for(int i=0; i<N; i++)
    {
        gr[i*2][i*2+1] = 1;
        c[i*2][i*2+1] = 1;
        c[i*2+1][i*2] = -1;
        gr[s][i*2] = 1;
        gr[i*2+1][t] = 1;    
    }
    
    int res = 0, flow=0;
    while(true)
    {
        res += spfa();
        flow++;
        
        int nd = t;

        while(nd!=s)
        {
            gr[nd][prv[nd]] = 1;
            gr[prv[nd]][nd] = 0;
            nd = prv[nd];
        }
        if(res == N) break;
    }
    cout<<flow;
}

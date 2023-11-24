#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, M, C;
vector<vector<pair<int,int>>> gr;
vector<ll>d, visited;
vector<vector<ll>> dp;

void dfs(int nd= N-1){
    visited[nd] = 1;
    for(auto [u, w] : gr[nd]){
        if(!visited[u]) dfs(u);
        
        for(int i=0; i<=100; i++)
            for(int j=i; j<=100; j++)
                for(int x = 0; x<=w; x++)
                    dp[nd][i+(w-x)] = min(dp[nd][i+(w-x)], max(dp[u][j],(ll) (d[nd] >> min(32, (j-i+x)))));
    }
}

int main(){
    cin>>N>>M>>C;
    gr.resize(N); dp.resize(N, vector<ll>(2000, LLONG_MAX));
    d.resize(N); visited.resize(N);
    for(auto& i:d) cin>>i;
    while(M--){
        int a, b, c; cin>>a>>b>>c;
        gr[b].push_back({a,c});
    }
    visited[0] = 1;
    
    int cost = d[0];
    for(int i=C; i>=0; i--){
        dp[0][i] = cost;
        cost/=2;
    }
    
    dfs();
    cout<<dp[N-1][0];
}

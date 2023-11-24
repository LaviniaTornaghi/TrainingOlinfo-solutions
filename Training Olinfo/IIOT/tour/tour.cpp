#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, K, v; ll res=0, d=0;
vector<vector<pair<int, ll>>> gr;
vector<bool>visited;

void dfs(int nd=0, ll val=0){
    if(val>d){
        d = val;
        v = nd;
    }
    visited[nd] = 1;
    for(auto [u, w] : gr[nd])
        if(!visited[u]) dfs(u, val+w);
}

int main(){
    cin>>N>>K;
    gr.resize(N);
    for(int i=0; i<N-1; i++){
        ll a, b, c; cin>>a>>b>>c;
        a--; b--;
        gr[a].push_back({b,c});
        gr[b].push_back({a,c});
        res += c*2;
    }

    if(K==1){
        cout<<res;
        return 0;
    }
    visited.resize(N);
    dfs();
    fill(visited.begin(), visited.end(), 0);
    d = 0;
    dfs(v);
    cout<<res-d;
}

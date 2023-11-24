#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> gr;
vector<bool> visited;
vector<int> v, res;
vector<int> val, inx;

void dfs(int nd){
    visited[nd] = 1;
    val.push_back(v[nd]);
    inx.push_back(nd);
    for(auto u : gr[nd])
        if(!visited[u]) dfs(u);
}

int main(){
    int N, K; cin>>N>>K;
    gr.resize(N); visited.resize(N);
    v.resize(N); res.resize(N);

    for(auto &i:v) cin>>i;
    while(K--){
        int l; cin>>l;
        for(int i=0; i+l<N; i++){
            gr[i].push_back(i+l);
            gr[i+l].push_back(i);
        }
    }
    
    for(int i=0; i<N; i++){
        val.clear(); inx.clear();
        if(!visited[i]){ 
            dfs(i);
            sort(val.begin(), val.end());
            sort(inx.begin(), inx.end());
            for(int k=0; k<val.size(); k++) res[inx[k]] = val[k];
        }
    }
    for(int i:res) cout<<i<<" ";
}

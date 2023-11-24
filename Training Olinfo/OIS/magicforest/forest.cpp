#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD (ll) (1e9+7)
int main(){
    int N, M; ll res=0; cin>>N>>M;
    vector<array<int, 3>> e; 
    vector<map<int, ll>> dp(N+1);
    
    while(M--){
        int a, b, c; cin>>a>>b>>c;
        e.push_back({-c, a, b});
    }
    sort(e.begin(), e.end());
    
    for(auto [w, v, u] : e){
        w = -w;
        ll fv = dp[v][w+1]+1;
        ll fu = dp[u][w+1]+1;
        res = (res + fv - 1)%MOD;
        res = (res + fu)%MOD;
        dp[v][w] = (dp[v][w]+fu)%MOD;
        dp[u][w] = (dp[u][w]+fv)%MOD;
    }
    cout<<res<<endl;
}

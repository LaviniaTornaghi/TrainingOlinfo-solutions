#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int N, K; cin>>N>>K;
    vector<int>v(N), c(N);
    vector<vector<ll>> dp(N, vector<ll>(K+1, -1));
    
    for(auto &i:v) cin>>i;
    for(auto &i:c) cin>>i;
    dp[0][min(K,c[0])] = v[0];
    
    for(int i=0; i<N-1; i++){
        dp[i+1][0] = dp[i][K];
        for(int j=0; j<=K; j++){
            if(dp[i][j] == -1) continue;
            int x = min(K, j+c[i+1]);
            if(dp[i+1][x]==-1) dp[i+1][x] = dp[i][j]+v[i+1];
            else dp[i+1][x] = min(dp[i+1][x], dp[i][j]+v[i+1]);
        }
    }

    for(int j=0; j<=K; j++){
        for(int i=0; i<N; i++) cout<<dp[i][j]<<" ";
        cout<<endl;
    }

    ll res=LLONG_MAX;
    for(int j=0; j<=K; j++)
        if(dp[N-1][j]!=-1) res = min(res, dp[N-1][j]);
    cout<<res;
}


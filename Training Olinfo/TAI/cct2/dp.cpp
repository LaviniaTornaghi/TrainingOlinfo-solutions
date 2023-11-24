#include <bits/stdc++.h>
using namespace std;
#define MOD (int)1000

int speedrunna(int N, int K, int a, int b){
    int v=1, c=1;
    vector<map<int,int>> dp(2);

    dp[0][min(K,c)] = v;
    
    for(int i=0; i<N-1; i++){
        v = (v*a)%MOD;
        c = (c*b)%K;
        if(dp[0].find(K)!=dp[0].end()) dp[1][0] = dp[0][K];
        for(auto [j, w] : dp[0]){
            int x = min(K, j+c);
            if(dp[1].find(x)==dp[1].end()) dp[1][x] = w+v;
            else dp[1][x] = min(dp[1][x], w+v);
        }
        dp[0] = dp[1];
        dp[1].clear();
    }

    int res=INT_MAX;
    for(auto [j, w] : dp[0]) res = min(res, w);
    return res;
}


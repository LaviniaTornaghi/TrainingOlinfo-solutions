#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll sq(ll a){
    return a*a;
}

int main(){
    ll N, H=0, res=LLONG_MAX; cin>>N;
    vector<ll>v(N);
    for(int i=0; i<N; i++){
        cin>>v[i];
        H = max(H, v[i]+2);
    }
    vector<vector<ll>> dp(N, vector<ll>(H, LLONG_MAX/2));

    for(int l=0; l<2; l++){
        for(int i=0; i<H; i++) dp[N-1][i] = sq(v.back()-i);
        for(int i=N-2; i>=0; i--){
            for(int h=0; h<H; h++){
                if(((l%2) && (i%2)) || (!(l%2) && !(i%2))){
                    for(int x = h+1; x<H; x++)
                        dp[i][h] = min(dp[i][h], sq(v[i]-h) + dp[i+1][x]);
                }
                else{
                    for(int x = 0; x<h; x++)
                        dp[i][h] = min(dp[i][h], sq(v[i]-h) + dp[i+1][x]);
                }   
            }
        }
        for(int i=0; i<H;i++) res = min(res, dp[0][i]);
        for(int i=0; i<N;i++) fill(dp[i].begin(), dp[i].end(), LLONG_MAX/2);
    }
    cout<<res<<endl;
}   

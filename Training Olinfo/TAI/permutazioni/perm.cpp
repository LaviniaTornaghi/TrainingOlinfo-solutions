#include <bits/stdc++.h>
using namespace std;
#define  ll long long
#define MOD (ll)(1e9+7)

int trova(int N){
 vector<ll>p(N+1,1); ll res=0;
 for(int i=1; i<=N; i++) p[i]=(p[i-1]*i)%MOD;
 for(int i=N-1; i>=3; i--) res = (res+p[i])%MOD;
 if(N<4) return p[N];
 return (res+p[3])%MOD;
}

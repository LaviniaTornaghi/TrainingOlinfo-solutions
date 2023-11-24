#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
#define MAXN 4002
#define HASH 2

int N, M;
string S;
vector<string> A;

ll fastexp (ll b, ll e){
    if(e==1) return b;
    ll tmp = fastexp(b, e/2);
    tmp *= tmp;
    tmp%=MOD;
    if(e%2) tmp *= b;
    tmp %= MOD;
    return tmp;
}

struct Hash{
    ll b;
    ll pow[MAXN], inv[MAXN];
    vector<ll> sh; //suffix hash of s
    vector<ll> h; //hash of the substrings

    void init(ll B){ //call after input
        b = B, pow[0] = 1; inv[0] = 1;
        for(int i=1; i<MAXN; i++){
            pow[i] = pow[i-1]*b;
            pow[i] %=MOD;
            inv[i] = fastexp(pow[i], MOD -2);
        }
        computa();
    }

    void computa(){
        sh.resize(N+1);
        sh[N-1] = S[N-1];
        for(int i= N-2; i>=0; i--){
            sh[i] = sh[i+1] + S[i]*pow[N-1-i];
            sh[i] %= MOD;
        }

        for(string x : A){
            ll tmp = x[0];
            for(int i=1; i<x.size(); i++){
                tmp = tmp*b + x[i];
                tmp%=MOD;
            }
            h.push_back(tmp);
        }
    }

    ll substring(int l, int r){ //R escluso
        ll tmp = (sh[l] - sh[r] + MOD);
        tmp%=MOD;
        tmp = tmp * inv[N-r];
        return tmp %= MOD;
    }

    bool cmp(int l, int r,int i){
        return substring(l, r) == h[i];
    }
};

Hash H[HASH];

int main(){
    cin>>N>>M;
    A.resize(M);
    cin>>S;
    for(auto& i:A) cin>>i;
    H[0].init(31); H[1].init(41);

    vector<ll> dp(N+1);
    dp[N] = 1;
    
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<M; j++){
            bool issame = true;
            if(A[j].size()+i > N) continue;
            for(int k = 0; k<HASH; k++){
                if(!H[k].cmp(i, i+A[j].size(), j)){
                    issame = 0;
                    break;
                }
            }
            if(issame){
                dp[i] += dp[i+A[j].size()];
                dp[i] %= MOD;
            }
        }
    }
    cout<<dp[0];
}

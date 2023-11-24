#include <bits/stdc++.h>
using namespace std;
#define MAXN 50005
#define ll long long
#define MOD (ll)2000000011
#define K 5

int N;
string S;

struct Hash
{
    ll b; //b per cui moltiplicare
    ll pow[MAXN];
    
    void init(ll B)
    {
        b = B;    
        pow[0] = 1;
        for(int i=1; i<MAXN; i++){ 
            pow[i] = pow[i-1]*b;
            pow[i]%=MOD;
        }
    }

    bool computa(int s)
    {
        ll H = S[0];
        for(int i=1; i<s; i++) H = ((b*H)%MOD + S[i]) %MOD;
        
        unordered_set<ll> z; z.insert(H);

        for(int i=s; i<N; i++)
        {
            H -= ((S[i-s]*pow[s-1])%MOD - MOD);
            H%=MOD;
            H = H*b;
            H%=MOD;
            H += S[i];
            H%=MOD;
            if(z.find(H) != z.end()) return true;
            z.insert(H);
        }
        return false;
    }
};

Hash h[K];

int main()
{
    h[0].init(29); h[1].init(31);
    h[2].init(37); h[3].init(41);
    h[4].init(43);
    cin>>N>>S;

    for(int i=0; i<N; i++) S[i]-= 'a';    
    
    int l= - 1, r = N;

    while(r-l > 1) 
    {
        int m = (l+r+1)/2;         

        bool isgood = 1;

        for(int i=0; i<K; i++)
             if(! h[i].computa(m)) isgood = 0;

        if(isgood) l = m;
        else r = m;  
    }

    bool isgooddavvero = 1;
    for(int i=0; i<K; i++) if(!h[i].computa(r)) isgooddavvero = 0;
    if(isgooddavvero) cout<<r;
    else cout<<l;
}

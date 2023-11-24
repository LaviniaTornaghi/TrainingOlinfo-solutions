#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define MOD (ll)(1e9+7)

int R, C, N, S;
vector<int> dsu, sz;
map<int, int> r, c, d1, d2;

int find(int a){
    if(dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

void join(int a, int b){
    a = find(a); b=find(b);
    if(a==b) return;
    if(sz[a]<sz[b]) swap(a,b);
    S--;
    dsu[b] = a;
    sz[a] += sz[b];

}

ll fastexp(ll b, ll e){
    if(!e) return 1;
    ll res = fastexp(b, e/2);
    res = (res*res)%MOD;
    if(e%2) res = (res*b)%MOD;
    return res;
}

int main(){
    cin>>R>>C>>N; S=N;
    dsu.resize(N); iota(dsu.begin(), dsu.end(),0);
    sz.resize(N, 1);
    for(int i=0; i<N; i++){
        int a, b; cin>>a>>b;
        if(r.find(a)!=r.end()) join(r[a], i);
        if(c.find(b)!=c.end()) join(c[b], i);
        if(d1.find(a-b)!=d1.end()) join(d1[a-b],i);
        if(d2.find(a+b)!=d2.end()) join(d2[a+b],i);
        r[a] = c[b] = d1[a-b] = d2[a+b] = i;
    }
    cout<<fastexp(2, S);
}

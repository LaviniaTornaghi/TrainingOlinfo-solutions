#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 500005
#define LOG 18

int N, M, t;
vector<array<ll, 3>> edges, sorted;
vector<vector<pair<int, ll>>> tree;
vector<int> dsu, tin , tout;
map<pair<ll,ll>, ll> mp;
set<array<ll, 3>> s;
ll mx[MAXN][LOG], Log[MAXN][LOG];

int find(int a){
    if(dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

int merge(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return 0;
    dsu[b] = a;
    return 1;
}

bool isa(int a, int b){ // is a ancestor of b
    return (tin[b] >= tin[a] && tout[b] <= tout[a]); 
}

void dfs(int nd, int prv, int parr){
    mx[nd][0] = parr;
    Log[nd][0] = prv;
    tin[nd] = t++;

    for(int i = 1; i<LOG; i++){
        Log[nd][i] = Log[Log[nd][i-1]][i-1];
        mx[nd][i] = max(mx[nd][i-1], mx[Log[nd][i-1]][i-1]);
    }
    for(auto [u, w] : tree[nd]){
        if(u != prv) dfs(u, nd, w);
    }
    tout[nd] = t++;
}

ll up(int v, int u){ //up from u to v
    ll res = 0;
    for(int i=LOG-1; i>=0; i--){
        if(!isa(Log[u][i], v)){
            res = max(res, mx[u][i]);
            u = Log[u][i];
        }
    }
    return max(res, mx[u][0]);
}

ll maxcose(int u, int v){
    if(isa(v, u)) return up(v, u);
    if(isa(u, v)) return up(u, v);
    return max( up(v, u), up (u, v));
}

int main(){
    cin>>M>>N;
    dsu.resize(N); tree.resize(N); tin.resize(N); tout.resize(N);
    while(M--){
        ll a, b, c; cin>>a>>b>>c;
        edges.push_back({a, b, c});
        sorted.push_back({c, a, b});
    }
    sort(sorted.begin(), sorted.end());
    
    ll cost = 0;
    iota(dsu.begin(), dsu.end(), 0);
    for(auto [x, y, z] : sorted){
        if(merge(y,z)){
                cost += x;
                if(z<y) swap(z,y);
                mp[make_pair(y,z)] =x;
                s.insert({y,z,x});
                tree[y].push_back({z, x});
                tree[z].push_back({y, x});
        }
    }
    dfs(0,0,0);

    for(auto [v, u, w] : edges){
        if(u<v) swap(u,v);
        if(s.find({v,u,w}) != s.end())cout<<cost<<"\n";
        else if(mp.find({v, u}) != mp.end()) cout<<cost + (w - mp[make_pair(v,u)]) <<"\n";
        else{
            cout<<cost + w - maxcose(v, u)<<"\n";
        }
    }
}

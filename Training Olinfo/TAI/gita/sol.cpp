#include <bits/stdc++.h>
using namespace std;

vector<int> b, ans, C; //beauty
map<int,int> inx;
vector<vector<int>> tree;
int tmp=1;

struct SegTree{
    vector<int> tree;
    int pos;

    void update(int pos, int value){
        tree[pos] = value;
        pos/=2;

        while(pos){
            tree[pos] = tree[pos*2] + tree[pos*2+1];
            pos/=2;
        }
    }

    int query(int c){
        pos = c;
        return query(1, 0, tmp-1);
    }

    int query(int inx, int l, int r){
        if(l == r) return l;
        int mid = (l+r)/2;
        if(tree[inx*2] < pos){
            pos -= tree[inx*2];
            return query(inx*2+1,mid+1, r);
        }
        else
            return query(inx*2, l, mid);
    }
};

SegTree st;

void dfs(int v=0, int p=-1, int d=0){ //d profondità
    st.update(b[v]+tmp, 1);
    
    if(d%2) ans[v] = INT_MAX;
    for(int u : tree[v]){
        if(u==p) continue;
        dfs(u, v, d+1);
        if(d%2) ans[v] = min(ans[v], ans[u]);
        else ans[v] = max(ans[v], ans[u]);
    }

    if(tree[v].size() == 1 && p!=-1)ans[v] = st.query(C[v]+1);
    
    st.update(b[v]+tmp, 0);
}

int visita(int N, vector<int> &A, vector<int> &B, vector<int> &dolcezza, vector<int> &c){
    vector<int> zip;
    b.resize(N); tree.resize(N); ans.resize(N); C.resize(N);
    //compression
    for(auto i : dolcezza) zip.push_back(i);
    sort(zip.begin(), zip.end());
    zip.resize(unique(zip.begin(), zip.end())-zip.begin());
    for(int i=0; i<N; i++){
         b[i] = lower_bound(zip.begin(), zip.end(), dolcezza[i]) - zip.begin();
         inx[b[i]] = dolcezza[i];
    }

    for(int i=0; i<N; i++) C[i] = c[i];
    while(tmp<=zip.size()) tmp*=2;
    st.tree.resize(2*tmp);

    for(int i=0; i<N-1; i++){
        tree[A[i]].push_back(B[i]);
        tree[B[i]].push_back(A[i]);
    }

    dfs();
    
    return inx[ans[0]];
}

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
vector<int> dfsorder, dfspos, ss;
int D,P,E, tmp=1;

void dfs(int v){
    dfspos[v] = dfsorder.size();
    dfsorder.push_back(v);

    for(auto u : tree[v])
        dfs(u);
    ss[v]=dfsorder.size()-dfspos[v];
}

struct SegTree{
    vector<int> tree, lazy, val;
    int sq, eq;
    int x, v;
    
    void init(){
        tree.resize(2*tmp);
        lazy.resize(2*tmp);
        val.resize(2*tmp);
    }

    void push(int nd, int l, int r){
        if(!lazy[nd]) return;
        lazy[nd] = 0;
        tree[nd] = val[nd];    
        if(l==r) return;
        lazy[nd*2] =lazy[nd*2+1] = 1;
        val[nd*2] = val[nd*2+1] = val[nd];
    }

    bool query(int i, int l, int r){
        push(i,l,r);
        if(l==r) return tree[i];
        int mid = (l+r)/2;
        if(x<=mid) return query(i*2,l,mid);
        else return query(i*2+1,mid+1,r);
    }

    bool query(int a){
        x = dfspos[a];
        return query(1, 0, tmp-1);
    }

    void update(int i, int l, int r){
        push(i,l,r);
        if(l>eq || r<sq) return;
        if(l>=sq && r<=eq){
            tree[i] = v;
            if(l!=r){
                lazy[i*2]=lazy[i*2+1]=1;
                val[i*2]=val[i*2+1] = v;
            }
            return;
        }
        int mid = (l+r)/2;
        update(i*2, l, mid);update(i*2+1,mid+1,r);
    }

    void update(int a, int b){
        v = b;
        sq = dfspos[a]; eq = dfspos[a]+ss[a]-1;
        update(1,0,tmp-1);
    }
};

int main(){
    cin>>D>>P>>E;
    tree.resize(D+P),dfspos.resize(D+P),ss.resize(D+P);

    for(int i=0; i<D+P; i++){
        int p; cin>>p;
        if(i)tree[p].push_back(i);
    }
    dfs(0); 
    while(tmp<=D+P) tmp*=2;
    SegTree st; st.init();
    
    while(E--){
        int a,b; cin>>a>>b;
        if(!a) st.update(b, 0);
        else if(a==1) st.update(b,1);
        else cout<<st.query(b)<<endl;
    }
}

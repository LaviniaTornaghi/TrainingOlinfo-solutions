#include <bits/stdc++.h>
using namespace std;
#define ll long long

int tmp=1, N;

struct SegTree{
    vector<ll>tree, v, ps, id;
    int sq, eq;

    void init(int sfere[]){
        ps.resize(N+1); v.resize(tmp); tree.resize(2*tmp);
        for(int i=0; i<=N; i++){
            id.push_back(rand()%(int)(1e12));
            if(i)ps[i] = ps[i-1] + id.back();
        }
        for(int i=0; i<N; i++) v[i] = id[sfere[i]];
        build(1,0,tmp-1);
    }

    void build(int i, int l, int r){
        if(l==r){
            tree[i] = v[i-tmp];
            return;
        }
        int mid = (l+r)/2;
        build(i*2, l, mid); build(i*2+1, mid+1, r);
        tree[i] = tree[i*2] + tree[i*2+1];
    }

    void update(int p, int v){ //già + tmp
        tree[p] = id[v];
        p/=2;

        while(p){
            tree[p] = tree[p*2]+tree[p*2+1];
            p/=2;
        }
    }

    bool query(int l, int r){
        sq = l; eq = r;
        return query(1,0,tmp-1) == (ps[r-l+1]);    
    }

    ll query(int i, int l, int r){
        if(l>eq || r<sq) return 0;
        if(l>=sq && r<=eq) return tree[i];
        int mid = (l+r)/2;
        return query(i*2, l, mid) + query(i*2+1, mid+1, r);
    }
};

SegTree st;

void inizio(int n,int M, int sfere[]){
    N = n;  while(tmp<=N) tmp*=2;
    st.init(sfere);
}
void modifica(int posizione,int valore){
    st.update(posizione+tmp, valore);
}
bool verifica(int l,int r){
    return st.query(l,r);
}

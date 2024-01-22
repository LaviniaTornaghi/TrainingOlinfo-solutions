#include <bits/stdc++.h>
using namespace std;

int N, tmp=1, res=1;
vector<int> v, mem;

struct SegTreeMax{
    vector<int> tree;
    int sq, eq=tmp-1;
    void init(){
        tree.resize(2*tmp, 0);
    }
    void update(int i, int v){ // non piu tmp
        i+=tmp;
        tree[i] = v;
        i/=2;
        while(i){
            tree[i] = max(tree[i*2],tree[i*2+1]);
            i/=2;
        }
    }
    int query(int l){
        sq = l; return query(1,0,tmp-1);
    }
    int query(int i, int l, int r){
        if(l>eq || r<sq) return 0;
        if(l>=sq && r<=eq) return tree[i];
        int mid = (l+r)/2;
        return max(query(i*2,l,mid),query(i*2+1,mid+1,r));
    }
};

struct SegTreeMin{
    vector<array<int,2>>tree;
    int sq, eq;
    void init(){
        tree.resize(2*tmp,{INT_MAX,-1});
        build(1,0,tmp-1);
    }
    void build(int i, int l, int r){
        if(l==r){
            tree[i] = {v[i-tmp],i-tmp};
            return;
        }
        int mid = (l+r)/2;
        build(i*2,l,mid), build(i*2+1,mid+1,r);
        if(tree[i*2][0]<=tree[i*2+1][0]) tree[i] = tree[i*2];
        else tree[i] = tree[i*2+1];
    }
    array<int,2>query(int l, int r){
        sq = l, eq = r;
        return query(1,0,tmp-1);
    }
    array<int,2>query(int i,int l, int r){
        if(l>eq || r<sq) return {INT_MAX,-1};
        if(l>=sq && r<=eq) return tree[i];
        int mid = (l+r)/2;
        array<int,2> a = query(i*2,l,mid), b = query(i*2+1,mid+1,r);
        if(a[0]<=b[0]) return a;
        return b;
    }
};

int main(){
    int N; cin>>N;
    while(tmp<=N) tmp*=2;
    v.resize(tmp);
    mem.push_back(0);
    for(int i=0;i<N; i++){
        cin>>v[i];
        mem.push_back(v[i]);
    }

    SegTreeMax stM; stM.init();
    SegTreeMin stm; stm.init();

    sort(mem.begin(),mem.end());
    mem.resize(unique(mem.begin(),mem.end())-mem.begin());
    for(auto &x : v)
        x = lower_bound(mem.begin(),mem.end(),x)-mem.begin();
    
    for(int i=0;i<N; i++){
        res = max(res, 1+i-stm.query(stM.query(v[i]+1),i)[1]);
        stM.update(v[i],i);
    }
    cout<<res;
}
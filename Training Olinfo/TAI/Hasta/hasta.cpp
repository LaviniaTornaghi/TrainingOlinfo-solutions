#include <bits/stdc++.h>
using namespace std;

struct Info
{
    vector<int> inx; //indici degli elementi deltipo
    int aumenta=-1; //dove aumenta
    int diminuisce=-1; //dove diminuisce
    int p; //persone per i-esima classe
    int conta=0;
};

struct Node
{
    int sum = 0;
    Node* l=NULL;
    Node*r=NULL;

    Node(){}

    Node(Node* copy)
    {
        sum = copy->sum;
        l= copy->l;
        r = copy->r;
    }
    
    Node(Node* L, Node* R)
    {
        l = L; r = R;
        if(l) sum += l->sum;
        if(r) sum += r->sum;
    }

    Node(int v)
    {
        sum = v;
    }
};

int N, tmp=1, K;
vector<Info> v;

struct SegTree
{
    vector<Node*> tree;

    void init()
    {
        tree.push_back(build(0, tmp-1));
    }

    Node* build(int l, int r)
    {
        if(l==r) return new Node();

        int mid = (l+r)/2;

        return new Node(build(l, mid), build(mid+1,r)); 
    }
    
    int pos, value;

    void update(int p, int v)
    {
        pos = p; value = v;
        tree.back() = update(tree.back(), 0, tmp-1);
    }

    Node* update(Node*nd, int l, int r)
    {
        if(l==r)
            return new Node(value);

        int mid = (l+r) /2;
        
        Node* tmp = new Node(nd->l, nd->r);

        if(pos<=mid)
            tmp->l = update(nd->l, l, mid);
        else
            tmp->r = update(nd->r, mid+1, r);

        tmp->sum = tmp->l->sum + tmp->r->sum;
        return tmp;
    }
    
    int sq, eq;

    int  query(int l, int r)
    {
        sq = l; eq = r;
        return query(tree[r], 0, tmp-1);
    }

    int  query(Node* nd, int l, int r)
    {
        if(l>eq || r<sq) return 0;

        if(l>=sq && r<= eq) return nd->sum;

        int mid = (l+r)/2;

        return query(nd->l, l, mid) + query(nd->r, mid+1, r);
    }
};

SegTree st;

void inizia(int n, int k, int V[], int Ki[])
{
    N = n; K=k;
    while(tmp<N) tmp*=2;
     
    v.resize(K);
    
    for(int i=0; i<k; i++) v[i].p= Ki[i];
        
    for(int i=0; i<N; i++)
         v[V[i]].inx.push_back(i);
       
    for(int i=0; i<N; i++)
    {
        if(!i) st.init();
        else
        st.tree.push_back(new Node(st.tree.back()));

        int value = V[i];
        
        v[value].conta++;

        if(v[value].conta < v[value].p) continue;

        if(v[value].aumenta==-1) // prima volta che incontriamo e worka
        {
            st.update(v[value].inx[0], v[value].p);
            v[value].aumenta = 0;
        }
        else if(v[value].diminuisce == -1)//aumenta e basta
        {
            st.update(v[value].inx[0], -v[value].p);
            st.update(v[value].inx[1], v[value].p);
            v[value].diminuisce = 0;
            v[value].aumenta = 1;
        }
        else
        {
            int diminuisce = v[value].diminuisce;
            st.update(v[value].inx[diminuisce], 0);
            st.update(v[value].inx[diminuisce+1], -v[value].p);
            st.update(v[value].inx[diminuisce+2], v[value].p);
            v[value].diminuisce++;
            v[value].aumenta++;
        }
    }
}

int istiga(int l, int r)
{
    return st.query(l, r);
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, tmp = 1;
vector<ll>v;

struct Node
{
	ll sum=0;
	ll lazy=0;
	Node*l=NULL;
	Node*r=NULL;
	
	Node(){}

	Node(ll  value)
	{
		sum = value;
	}

	Node(Node* L, Node* R)
	{
		l = L; r = R;
		if(l) sum += l->sum;
		if(r) sum += r->sum;
	}

	Node(Node* copy)
	{
		if(!copy) return;
		sum = copy->sum;
		lazy = copy->lazy;
		l = copy->l;
		r = copy->r;
	}

	Node(Node* copy, ll LAZY)
	{
		sum = copy->sum;
		lazy = copy->lazy + LAZY;
		l = copy->l;
		r = copy->r;
	}

	Node(Node* copy, ll add, ll LAZY)
	{
		sum = copy->sum + add;
		l = copy->l;
		r = copy->r;
		if(l) l->lazy += LAZY;
		if(r) r->lazy += LAZY;
	}

	Node(Node*copy, Node*L, Node*R, ll add, ll LAZY)
	{
		sum = copy->sum + add;
		l = L; r = R;
		if(l) l->lazy += LAZY;
		if(r) r->lazy += LAZY;
	}
};

struct SegTree
{
	vector<Node*> tree;
	int sq, eq;
	ll value;
	
	void push(Node* &nd, int l, int r)
	{
		if(nd->lazy)
		{
			nd->sum += (r-l+1)*nd->lazy;
			if(nd->l) nd->l = new Node(nd->l,nd->lazy);
			if(nd->r) nd->r = new Node(nd->r,nd->lazy);

			nd->lazy=0;
		}
	}

	Node* build(int l, int r)
	{
		if(l==r)
			return new Node(v[l]);
		if(l>N) return new Node();
		int mid = (l+r)/2;	
		return new Node(build(l, mid), build(mid+1, r));
	}

	void update(int s, int e, int delta)
	{
		sq = s; eq = e-1; value = delta;
		tree.push_back(new Node(update(tree.back(), 0, tmp-1)));
	}

	Node* update(Node* nd, int l, int r)
	{
		push(nd, l, r);
				
		if(l>eq || r<sq) return nd;
		
		if(l>=sq && r<=eq) 
		{
			return new Node(nd,new Node(nd->l), new Node(nd->r), value*(r-l+1), value);
		}

		int mid = (l+r)/2;
		
		return new Node(update(nd->l, l, mid), update(nd->r, mid+1, r));
	}

	void reset(int l, int r, int v)
	{
		sq = l; eq = r-1;
		tree.push_back(new Node(reset(tree[v], tree.back(), 0, tmp-1)));
	}

	Node* reset(Node* nd, Node* copy, int l, int r)
	{
		push(nd, l, r);
		push(copy, l, r);

		if(l>eq || r<sq) return copy;
					
		if(l>=sq && r<=eq) return nd;
		
		int mid = (l+r)/2;
		
		return new Node(reset(nd->l, copy->l, l, mid), reset(nd->r, copy->r, mid+1, r));

	}
	
	ll res;

	ll  query(int s, int e)
	{
		sq = s; eq = e-1; res = 0;
		tree.back() =  query(tree.back(), 0 , tmp-1);
		return res;
	}

	Node*  query(Node* nd, int l, int r)
	{
		push(nd, l, r);
	
		if(l>eq || r<sq) return nd;

		if(l>=sq && r<=eq)
		{
			res += nd->sum;
			return nd;
		}

		int mid = (l+r) / 2;

		return new Node(query(nd->l, l, mid), query(nd->r, mid+1, r));
	}
};

SegTree st;

void inizia(int n, vector<int> A)
{
	while(tmp<n) tmp*=2;
	v.resize(tmp); for(int i=0; i<n; i++) v[i] = A[i];
	N = n;
	st.tree.push_back(st.build(0, tmp-1));
}

void incrementa(int l, int r, int x)
{
	st.update(l, r, x);
}

void resetta(int l, int r, int v)
{
	st.reset(l, r, v);
}

long long somma(int l, int r)
{
	return st.query(l,r);
}

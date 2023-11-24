#include <bits/stdc++.h>
using namespace std;

int N, tmp=1;

struct Node
{
	int sum=0;
	Node* l;
	Node* r;

	Node()
	{
		sum = 0;
		l = NULL;
		r = NULL;
	}
	Node(Node* L, Node* R)
	{		
		l = L;
		r = R;
		if(l) sum += l->sum;
		if(r) sum += r->sum;
	}

	Node(int value)
	{
		sum = value;
		l = NULL;
		r = NULL;
	}

	Node(Node * nd)
	{
		sum = nd->sum;
		l = nd->l;
		r = nd->r;
	}
};

struct SegTree
{
	vector<Node*> tree;
	
	void init()
	{
		tree.push_back(build(0, tmp-1));
//		print(tree[0]);
	}

	Node*  build(int l, int r)
	{
		if(l==r)
		{
			return new Node();	
		}
		int mid = (l+r)/2;
		return new Node(build(l, mid), build(mid+1, r));
	}
	
	int pos, value;

	Node* update(Node* nd, int l, int r)
	{
		if(l==r && l == pos)
		{
			return new Node(value);
		}
		else if(l==r) return nd;

		int mid = (l+r)/2;

		Node* tmp = new Node(nd->l, nd->r);

		if(pos<=mid)
			tmp->l =new Node( update(tmp->l, l, mid));
		else
			tmp->r =new Node( update(tmp->r, mid+1, r));
		
		tmp->sum = tmp->l->sum + tmp->r->sum;
		return tmp;
	}

	void print(Node* nd)
	{
		cout<<nd->sum<<" ";
		if(nd->l) print(nd->l);
		if(nd->r) print(nd->r);
	}

	int sq, eq;

	int query(Node* nd, int l, int r)
	{
		if(l>eq || r<sq) return 0;
		if(l>=sq && r<=eq) return nd->sum;

		int mid = (l+r)/2;

		return query(nd->l, l, mid) + query(nd->r, mid+1, r);
	}

};

SegTree st;

void init(int n)
{
	N = n;
	while(tmp<N) tmp*=2;
	st.init();	
}

void log(vector<int>& added, vector<int>& removed)
{
	st.tree.push_back(new Node(st.tree.back()));
	for(auto i : added)
	{
		st.value = 1; st.pos = i;
		st.tree.back()= st.update(st.tree.back(), 0, tmp-1);
	}

	for(auto i: removed)
	{
		st.value = 0; st.pos = i;
		 st.tree.back()= st.update(st.tree.back(), 0, tmp-1);
	}
}

int answer(int d, int y)
{
	st.sq = y; st.eq = N-1;
	return st. query(st.tree[d], 0, tmp-1);
}

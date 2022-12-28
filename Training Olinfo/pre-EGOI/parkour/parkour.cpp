#include <bits/stdc++.h>
using namespace std;
#define sx inx*2
#define dx inx*2+1
#include "grader.cpp"

vector<int> v;
int tmp, N=1;

struct SegTree
{
	vector<int> tree;
	int qs, qe;
	
	void build(int inx, int l, int r)
	{
		if(l==r)
		{
			tree[inx] = v[inx-N];
			return;
		}
		int mid = (l+r)/2;
		build(sx, l, mid); build(dx, mid+1, r);
		tree[inx] = min(tree[sx], tree[dx]);
	}
	
	void update(int pos, int value) //N+pos
	{
		tree[pos] = value;
		if(pos<(N+tmp-1))
			tree[pos] = max(v[pos-N], tree[pos]);
		pos/=2;
		while(pos)
		{
			tree[pos] = min(tree[pos*2], tree[pos*2+1]);
			pos/=2;
		}
	}
	
	void print()
	{
		for(int i=N; i<2*N; i++) cout<<tree[i]<<" ";
	}
	
	int query(int inx, int l, int r)
	{
		if(l>qe || r<qs) return INT_MAX;
		if(l>=qs && r<=qe)
			return tree[inx];
			
		int mid = (l+r)/2;
		return min(query(sx, l, mid) , query(dx, mid+1, r));
	}
};

SegTree st;

int salta(int n, vector<int> S, vector<int> A, vector<int> B)
{
	tmp = n+1; //consideriamo anche il parco
	while(N<tmp) N*=2;

	v.resize(N, INT_MAX);
	st.tree.resize(2*N);
	for(int i=0; i<n; i++) v[i] = S[i];
	
	st.build(1, 0, N-1);
	st.tree[N+n-1] = S.back();
	for(int i=n-2; i>=0; i--)
	{
		st.qs = i+A[i]; st.qe = i+B[i];
		if(i+B[i]==n) st.update(N+i, S[i]);
		else
		{
			int value = st.query(1, 0, N-1);
			st.update(N+i, value);
		}
	}
	//st.print();
	return st.tree[N];
}

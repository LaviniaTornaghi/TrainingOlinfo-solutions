#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int tmp, N=1;

struct SegTree
{
	vector<int> tree;
	int qs, qe;

	void update(int pos, int value) //N+pos
	{
		tree[pos] = max(v[pos-N],value);
		pos/=2;
		while(pos)
		{
			tree[pos] = min(tree[pos*2], tree[pos*2+1]);
			pos/=2;
		}
	}

	int query(int inx, int l, int r)
	{
		if(l>qe || r<qs) return INT_MAX;
		if(l>=qs && r<=qe) return tree[inx];
			
		int mid = (l+r)/2;
		return min(query(inx*2, l, mid) , query(inx*2+1, mid+1, r));
	}
};

int salta(int n, vector<int> S, vector<int> A, vector<int> B)
{
	Segtree st;
	tmp = n+1; 
	while(N<tmp) N*=2;
	v.resize(N, 0);
	st.tree.resize(2*N);
	for(int i=0; i<n; i++) v[i] = S[i];

	for(int i=n-1; i>=0; i--)
	{
		if(i+B[i]==n) 
		{
			st.update(N+i, S[i]);
			continue;
		}
		st.qs = i+A[i]; st.qe = i+B[i];
		st.update(N+i, st.query(1,0,N-1));
	}
	return st.tree[N];
}

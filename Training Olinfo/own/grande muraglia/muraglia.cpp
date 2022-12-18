#include <bits/stdc++.h>
using namespace std;
#include "grader.cpp"
int N;
int tmp;

struct SegTree
{
	vector<int> tree;
	
	void build(int inx, int l, int r)
	{
		if(l==r) return;
		int mid =(l+r)/2;
		
		build(2*inx, l, mid);
		build(2*inx+1, mid+1, r);
		tree[inx] = max(tree[inx*2], tree[inx*2+1]);
	}
	
	void print()
	{
		for(int i=1; i<2*N; i++) cout<<tree[i]<<" ";
	}
	
	int sq, eq;
	int res;
	int x;
	
	void left_bound(int inx, int l, int r)
	{
		
		if(l>eq || r<sq) return;
		if(l==r)
		{
			if(tree[inx]>x)
				res = inx-N; //returno la foglia, devo ancora trogliere N
			return;
		}
		
		int mid=(l+r)/2;
		
		if(r<=eq)
		{
			if(eq<=mid)
			{
				left_bound(inx*2, l, mid);
			}
			else if(tree[inx*2+1]>x)
			{
				left_bound(inx*2+1, mid+1, r);
			}
			else left_bound(inx*2, l, mid);
			
			return;
		}
		left_bound(inx*2, l, mid);
		left_bound(inx*2+1, mid+1, r);
	}
	
	void right_bound(int inx, int l, int r)
	{
	//	cout<<inx<<" "<<l<<" "<<r<<endl;
		
		if(l>eq || r<sq) return;
		if(l==r)
		{
			if(res!=-1) return;
			
			if(tree[inx]>x)
			{
				
			//cout<<"aggiorna qua\n"<<tree[inx]<<" "<<x<<endl;
				res = inx -N;
			}
			return;
		}
		
		int mid = (l+r) /2;
		
		if(l>=sq)
		{
			if(sq>mid)
			{
				right_bound(inx*2+1, mid+1, r);
			}
			else if(tree[inx*2]>x)
			{
				right_bound(inx*2, l, mid);
			}
			else right_bound(inx*2+1, mid+1, r);
			
			return;
		}
		right_bound(inx*2, l, mid);
		right_bound(inx*2+1, mid+1, r);
	}
	
	void update(int pos, int value)
	{
		tree[pos] = value;
		pos /=2;
		
		while(pos>0)
		{
			tree[pos] = max(tree[pos*2], tree[pos*2+1]);
			pos /=2;
		}
	}
	
};

SegTree st;

void inizializza(int n, vector<int> H)
{
	N=n;
	tmp=n;
	N=1;
	while(N<tmp) N*=2;
	st.tree.resize(2*N,0);
	for(int i=N; i<N+tmp; i++) st.tree[i] = H[i-N];
	st.build(1, 0, N-1);
}

void cambia(int x, int h)
{
	st.update(x+N, h);
	//st.print();
}

pair<int, int> chiedi(int x)
{
	pair<int,int> p;
	
	st.sq = 0;
	st.eq = x-1;
	st.x = st.tree[N+x];
	st.res = 0;
	st.left_bound(1, 0, N-1);
	p.first = st.res;
	st.sq = x+1;
	st.eq = N-1;
	st.res = -1;
	st.right_bound(1, 0, N-1);
	if(st.res==-1) st.res = tmp-1;
	p.second=st.res;
	return p;
}


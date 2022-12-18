#include <bits/stdc++.h>
using namespace std;
#define ll long long 

int N, tmp;
vector<int>v;

struct Nodo
{
	ll sum; //sum
	ll ps; //max prefix
	ll ss; //max suffix
	ll ms; //max sum 
};

struct SegTree
{
	vector<Nodo> tree;
	
	void init()
	{
		tree.resize(2*N, {0, 0, 0, LLONG_MIN});
		build(1, 0, N-1);
	}
	
	void build(int inx, int l, int r)
	{
		if(l==r) 
		{
			if(inx-N>=0 && inx-N<tmp && inx!=N)
				tree[inx].sum = tree[inx].ps = tree[inx].ss = tree[inx].ms = v[inx - N];
			else 
				tree[inx] = {0,0,0, LLONG_MIN};
			return;
		}
		int mid = (l+r)/2;
		build(inx*2, l, mid);
		build(inx*2+1, mid +1, r);
		
		tree[inx].sum = tree[inx*2].sum + tree[inx*2+1].sum;
		tree[inx].ps = max(tree[inx*2].ps, tree[inx*2].sum + tree[inx*2+1].ps);
		tree[inx].ss = max(tree[inx*2+1].ss, tree[inx*2+1].sum + tree[inx*2].ss);
		tree[inx].ms = max({tree[inx*2].ms, tree[inx*2+1].ms, tree[inx*2].ss+ tree[inx*2+1].ps});
	}
	
	void update(int inx, int value) //gia passato come pos + N
	{
		tree[inx].sum = tree[inx].ps = tree[inx].ss = tree[inx].ms = value;
		inx/=2;
		
		while(inx>0)
		{
			
			tree[inx].sum = tree[inx*2].sum + tree[inx*2+1].sum;
			tree[inx].ps = max(tree[inx*2].ps, tree[inx*2].sum + tree[inx*2+1].ps);
			tree[inx].ss = max(tree[inx*2+1].ss, tree[inx*2+1].sum + tree[inx*2].ss);
			tree[inx].ms = max({tree[inx*2].ms, tree[inx*2+1].ms, tree[inx*2].ss+ tree[inx*2+1].ps});
			inx /= 2;
		}
	}
	
	Nodo res;
	int sq, eq;
	bool first;
	void query(int inx, int l, int r)
	{
		if(l>eq||r<sq) return;
	
		if(l>=sq && r<=eq)
		{
			if(first)
			{
				res = tree[inx];
				first = false;
			}
			else //merge
			{
				Nodo tmp = res;
				res.sum = tmp.sum + tree[inx].sum;
				res.ps = max(tmp.ps, tmp.sum + tree[inx].ps);
				res.ss = max(tree[inx].ss, tree[inx].sum + tmp.ss);
				res.ms = max({tmp.ms, tree[inx].ms, tmp.ss + tree[inx].ps});
			}
			return;
		}
		int mid = (l+r)/2;
		query(inx*2, l, mid);
		query(inx*2+1, mid+1, r);
	}
	
	void print()
	{
		for(int i=0; i<2*N; i++) cout<<tree[i].ss<<" ";
		cout<<endl;
	}
};

SegTree st[2];

int main()
{
	int Q;
	cin>>N>>Q;
	N++;
	v.resize(N);
	tmp = N;
	N=1;
	while(N<tmp) N*=2;
	
	for(int i=1; i<tmp; i++) 
	{
		cin>>v[i];
		if(i%2) v[i] = -v[i];
	}
	st[0].init(); //posizioni dispari sono negative
	
	for(int i=1; i<tmp; i++) v[i] = -v[i];
	
	st[1].init(); //posizioni pari sono negative

	for(int q=0; q<Q; q++)
	{
		int tipo;
		cin>>tipo;
		
		if(tipo == 1)
		{
			int a, b;
			cin>>a>>b;
			
			if(a%2) //posizione dispari
			{
				a+=N;
				st[0].update(a, -b);
				st[1].update(a, b);
			}
			else
			{
				a+=N;
				st[0].update(a, b);
				st[1].update(a, -b);
			}
		}
		else
		{
			int l, r;
			cin>>l>>r;
			st[0].sq = st[1].sq = l;
			st[0].eq = st[1].eq = r;
			st[0].first = st[1].first = true;
			st[0].query(1, 0, N-1);
			st[1].query(1, 0, N-1);
			ll risdispari = st[0].res.ms;
			ll rispari = st[1].res.ms;
			
			cout<<max(risdispari,rispari)<<endl;
			
		}
	}
}

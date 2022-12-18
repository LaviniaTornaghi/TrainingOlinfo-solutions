#include <bits/stdc++.h>
using namespace std;
#include "grader.cpp"

struct Nodo
{
	vector<int>figli;
	int padre;
};

int N;
int t=0;
vector<int> p; //pericolosità
vector<vector<int>> tmp;
vector<Nodo>tree;
vector<int>tin;
vector<int> tout;
int Log[100005][18];
int mx[100005][18];

void Ancestors(int nd)
{
	if(nd==0) return;
	Log[nd][0] = tree[nd].padre;
	mx[nd][0] = max(p[nd], p[tree[nd].padre]);
	
	for(int i=1; i<18; i++)
	{
		Log[nd][i] = Log[Log[nd][i-1]][i-1];
		mx[nd][i] = max(mx[nd][i-1], mx[Log[nd][i-1]][i-1]);
	}
}

void build(int nd, int prec)
{
	tree[nd].padre = prec;
	Ancestors(nd);
	tin[nd] = ++t;
	for(int i=0; i<tmp[nd].size();i++)
	{
		if(tmp[nd][i]!=prec)
		{
			tree[nd].figli.push_back(tmp[nd][i]);
			build(tmp[nd][i], nd);
		}
	}
	tout[nd] = ++t;
}

bool isa(int a, int b) //a ancestor di b
{
	return (tin[a]<= tin[b] && tout[a]>=tout[b]);
}

int up(int a, int b) //soluzione risalendo da a a b
{
	int res = p[a];
	for(int i=17; i>=0; i--)
	{
		if(!isa(Log[a][i], b))
		{
			res = max(res, mx[a][i]);
			a = Log[a][i];
		}
	}
	res = max(res, p[tree[a].padre]);
	return res;
}

int query(int a, int b)
{
	if(isa(a,b)) return up(b, a);
	if(isa(b,a)) return up(a, b);
	
	return max(up(a, b), up(b,a));
}

void solve(int n, int Q, int *briganti, int *A, int *B, int *start, int *end, int *sol)
{
	N = n;
	p.resize(N);
	tmp.resize(N);
	tree.resize(N);
	tin.resize(N); tout.resize(N);
	for(int i=0; i<N; i++) p[i] = briganti[i];
	for(int i=0; i<N-1; i++)
	{
		tmp[A[i]].push_back(B[i]);
		tmp[B[i]].push_back(A[i]);
	}
	
	for(int i=0; i<17; i++) 
	{
		Log[0][i] = 0;
		mx[0][i] = p[0];
	}
	build(0, -1);
	
	for(int q=0; q<Q; q++) sol[q] = query(start[q], end[q]);
}

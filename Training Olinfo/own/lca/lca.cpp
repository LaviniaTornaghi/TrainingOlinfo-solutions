#include <bits/stdc++.h>
using namespace std;
#include "grader.cpp"
#define ll long long

struct Arco
{
	int b; //figlio
	ll p; //peso
};

struct Info
{
	ll ps;
	ll ss;
	ll ms;
	ll sum;
};

vector<vector<pair<int,ll>>> tmp;
vector<int> tin;
vector<int> tout;
vector<vector<Arco>> tree;
int Log[100005][18]; //lca
ll sum[100005][18]; //somma cose
ll minim[100005][18]; //minimo cose
Info st[100005][18]; //massima sottovettore somma
int t=0;

void merge(Info *i1, Info *i2, Info *na)
{
	na->sum = i1->sum + i2->sum;
	na->ps = max(i1->ps, i1->sum + i2->ps);
	na->ss = max(i2->ss, i2->sum + i1->ss);
	na->ms = max({i1->ms, i2->ms, i1->ss+i2->ps});
}

void ancestors(int nd)
{
	for(int i=1; i<18; i++)
	{
		sum[nd][i] = sum[nd][i-1]+sum[Log[nd][i-1]][i-1];
		minim[nd][i] = min(minim[nd][i-1], minim[Log[nd][i-1]][i-1]);
		Log[nd][i] = Log[Log[nd][i-1]][i-1];
		merge(&st[nd][i-1],&st[Log[nd][i-1]][i-1],&st[nd][i]);
	}
}

bool isa(int a, int b) // is a ancestor di b
{
	if(tin[a]<=tin[b] && tout[a]>=tout[b])
		return true;
	return false;
}

ll up(int a, int b) // risali da a a b
{
	ll res = 1;

	for(int i=17; i>=0; i--)
	{
		if(!isa(Log[a][i],b))
		{
			res += (1<<i);
			a = Log[a][i];
		}
	}
	return res;
}

ll sommacose(int a, int b) //somma salendo da a ad b
{
	ll res = 0;
	
	for(int i=17; i>=0; i--)
	{
		if(!isa(Log[a][i],b))
		{
			res += sum[a][i];
			a = Log[a][i];
		}
	}
	res += sum[a][0];
	return res;
}

ll minimizzacose(int a, int b) // query sul minimo
{
	ll res = LLONG_MAX;
	
	for(int i=17; i>=0; i--)
	{
		if(!isa(Log[a][i], b))
		{
			res = min(minim[a][i], res);
			a = Log[a][i];
		}
	}
	res = min(minim[a][0], res);
	return res;
}

Info maxss(int a, int b)
{
	Info res, tmp;
	bool isfirst = true;

	for(int i=17; i>=0; i--)
	{
		if(!isa(Log[a][i],b))
		{
			if(isfirst)
			{
				res = st[a][i];
				isfirst = 0;
			}
			else
			{	
				merge(&res, &st[a][i], &tmp);
				res = tmp;
			}
			a = Log[a][i];
		}
	}
	if(isfirst) return st[a][0];
	else merge(&res, &st[a][0], &tmp);
	return tmp;
}

long long distanza1(int u, int v)
{
	if(u==v) return 0;
	if(isa(u,v)) return up(v,u);
	if(isa(v,u)) return up(u,v);
	return up(v,u) + up(u,v);
}

long long distanza2(int u, int v)
{
	if(u==v) return 0;
	if(isa(u,v)) return sommacose(v,u);
	if(isa(v,u)) return sommacose(u,v);
	return sommacose(v,u) + sommacose(u,v);
}

long long minimo(int u, int v)
{
	if(isa(u,v)) return minimizzacose(v,u);
	if(isa(v,u)) return minimizzacose(u,v);
	return min(minimizzacose(u,v), minimizzacose(v,u));
}

long long massimo(int u, int v)
{
	if(u==v) return 0;
	if(isa(u,v))return maxss(v,u).ms;
	if(isa(v,u))return maxss(u,v).ms;
	Info res1 = maxss(v,u);
	Info res2 = maxss(u,v);
	return max({res1.ms, res2.ms, res1.ss+res2.ss});
}

void init(int nd, int padre, ll parcoarr)
{
	Log[nd][0] = padre;
	sum[nd][0] = parcoarr;
	minim[nd][0] = parcoarr;
	ll value = max((ll)0, parcoarr);
	st[nd][0] = {value,value,value,parcoarr};
	ancestors(nd);
	tin[nd] = ++t;
	
	for(int i=0; i<tmp[nd].size(); i++)
	{
		if(tmp[nd][i].first != padre)
		{
			tree[nd].push_back({tmp[nd][i].first, tmp[nd][i].second});
			init(tmp[nd][i].first, nd, tmp[nd][i].second);
		}
	}
	tout[nd] = ++t;
}

void inizia(int N, int T, int A[], int B[], int C[])
{
	tmp.resize(N); tin.resize(N); tout.resize(N); tree.resize(N);
	
	for(int i=0; i<N-1; i++)
	{
		tmp[A[i]].push_back({B[i],C[i]});
		tmp[B[i]].push_back({A[i], C[i]});
	}
	init(0, 0, 0);
}

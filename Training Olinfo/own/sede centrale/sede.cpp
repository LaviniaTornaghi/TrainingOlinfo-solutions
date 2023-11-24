#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Arco
{
	int b, p;
};

vector<vector<Arco>> tree;
vector<bool> f;
vector<ll> dp;
vector<ll> conta;
ll res = LLONG_MAX; int inx;

void dfs(int nd, int p=-1)
{
	if(tree[nd].size()==1 && p!=-1) return;

	for(auto [b,c] : tree[nd])
	{
		if(b==p) continue;
		dfs(b, nd);

		dp[nd] += (dp[b] + c*conta[b]);
		conta[nd] += conta[b];

		if(f[b])
		{
			conta[nd]++;
			dp[nd] += c;
		}
	}
}

void rerooting(int nd, int p=-1, ll  dpup=0, ll  nup=0)
{
	if(res > dp[nd] + dpup)
	{
		res = dp[nd] + dpup;
		inx = nd;
	}
		
	for(auto [b, c] : tree[nd])
	{
		if(b==p) continue;

		ll  newnup = nup + conta[nd]-conta[b];
		if(f[b]) newnup--;

		ll newdpup = newnup*c + dpup + dp[nd] - dp[b] - c*(conta[b]);

		if(f[b]) newdpup -= c;
		
		if(f[nd])
		{
			newnup++;
			newdpup += c;
		}

		rerooting(b, nd, newdpup, newnup);
	}	
}

int trova_sede(int N, int K, int A[], int B[], int P[], int fliali[])
{
	tree.resize(N+1); f.resize(N+1); dp.resize(N+1);
	conta.resize(N+1);
	for(int i=0; i<N-1; i++)
	{
		tree[A[i]].push_back({B[i], P[i]});
		tree[B[i]].push_back({A[i], P[i]});
	}

	for(int i=0; i<K; i++) f[fliali[i]] = 1;

	dfs(1);
	rerooting(1);

	return inx;
}

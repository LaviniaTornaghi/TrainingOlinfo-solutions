#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define in :

vector<vector<int>> tree;
vector<int> dp, sol;
int N;

struct Mx {int n, v;};

void dfs1(int nd, int p)
{
	int res = 1, mx = 0;
	
	for(auto figlio in tree[nd])
	{
		if(figlio == p) continue;
		dfs1(figlio, nd);
		res += dp[figlio];
		mx = max(mx, dp[figlio]);
	}
	dp[nd] = res - mx;
}

void dfs2(int nd, int p, int up)
{
	int res = 1;
	Mx mx[2] = {{0,0}, {0,0}};
	int mxson=0;
	
	for(auto figlio in tree[nd])
	{
		if(figlio == p) continue;
		
		res += dp[figlio];
		
		if(dp[figlio] > mx[0].v)
		{
			mx[1] = mx[0];
			mx[0] = {figlio, dp[figlio]};
			mxson = dp[figlio];
		}
		else if(dp[figlio] > mx[1].v)
		{
			mx[1] = {figlio, dp[figlio]};
		}
	}
	sol[nd] = res + up - max(mxson, up);
	
	for(auto figlio in tree[nd])
	{
		if(figlio == p) continue;
		if(figlio == mx[0].n) //sto andando nel massimo
		{
			int newup = up + res - dp[figlio] - max(up, mx[1].v);
			dfs2(figlio, nd, newup);
		}
		else
		{
			int newup = up + res - dp[figlio] - max(up, mx[0].v);
			dfs2(figlio, nd, newup);
		}
	}
}

int main()
{
	cin>>N;
	tree.resize(N); dp.resize(N,0); sol.resize(N);
	for(int i=0; i<N-1; i++)
	{
		int a, b; cin>>a>>b;
		tree[a].pb(b);
		tree[b].pb(a);
	}
	
	dfs1(0, -1);
	dfs2(0, -1, 0);
	
	for(auto it : dp) cout<<it<<" ";
	return 0;
	
	for(int i=0; i<N; i++) cout<<sol[i]<<" ";
}

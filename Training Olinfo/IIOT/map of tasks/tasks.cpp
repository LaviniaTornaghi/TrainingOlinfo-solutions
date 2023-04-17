#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, C, root;
vector<vector<int>>gr;
vector<ll> p; //peso dell'iesimo nodo
vector<int>dfs;
vector<bool> visited;

void d(int nd)
{
	visited[nd] = 1;

	for(auto u: gr[nd])
		if(!visited[u])
			d(u);
	dfs.push_back(nd);
}

int main()
{
	cin>>N>>C;
	gr.resize(N); 
       	visited.resize(N); p.resize(N);
	
	for(int i=0; i<N; i++)
	{
		int a, b; cin>>a>>b;
		if(a==-1) root = i;
		else gr[a].push_back(i);
		p[i] = b;
	}
	d(root);
	
	vector<vector<ll>> dp(N,vector<int>(C+1));

	for(auto nd : dfs)
	{
		int t = gr[nd].size();

		if(!t)
		{
			dp[nd][0] = p[nd];
			continue;	
		}
		
		vector<ll>v(t), inx(t); //da ogni figlio quanto pesa il path, v, quanti ne ho presi inx
			
		for(int i=0; i<gr[nd].size(); i++) v[i] = dp[gr[nd][i]][0];

		auto rm = max_element(v.begin(), v.end());
		dp[nd][0] = *rm	+ p[nd];

		for(int i=1; i<=C; i++)
		{
			int pos = rm - v.begin();
			v[pos] = dp[gr[nd][pos]][inx[pos]+1];
			inx[pos]++;
			
			rm = max_element(v.begin(), v.end());
			dp[nd][i] = p[nd] + *rm;
		}

		for(int i=C; i>0; i--)
			dp[nd][i] = min(dp[nd][i], dp[nd][i-1] - p[nd]);
	}
	cout<<dp[root][C];
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include "grader.cpp"

vector<ll>v;
vector <vector<int>> tree;

int Log[1000006][21];
ll sum[1000006][21];

void dfs(int nd, int padre)
{
	Log[nd][0] = padre;
	sum[nd][0] = (v[nd])*(padre-nd);
	for(int i=1; i<21; i++)
	{
		Log[nd][i] = Log[Log[nd][i-1]][i-1];
		sum[nd][i] = sum[nd][i-1] + sum[Log[nd][i-1]][i-1];
	}
	
	for(int i=0; i<tree[nd].size(); i++) dfs(tree[nd][i], nd);
}

void inizia(int N, int T[]) 
{
	stack<pair<int,int>> s; //first = value, second = index
	v.resize(N+1); tree.resize(N+1);
	
	for(int i=0; i<N; i++) v[i] = T[i];
	v[N] = 0;
	s.push({-1, N});
	
	for(int i=N-1; i>=0; i--)
	{
		while(s.top().first>=v[i]) s.pop();
		tree[s.top().second].push_back(i);
		s.push({v[i], i});
	}
	dfs(N, N);
	/*
	 cout<<endl;
	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<3; j++)
			cout<<mn[i][j]<<" ";
		cout<<endl;
	}*/
	
}

long long passaggio(int a, int b) 
{
  ll res = 0;
  for(int i=20; i>=0; i--)
  {
	  if(Log[a][i]<=b)
	  {
		  res += sum[a][i];
		  a= Log[a][i];
		  if(a==b) break;
	  }
  }
  if(a!=b) res += (b-a)*v[a];
  return res;
}

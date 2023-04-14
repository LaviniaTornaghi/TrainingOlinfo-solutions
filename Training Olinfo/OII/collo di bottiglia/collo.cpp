#include <bits/stdc++.h>
using namespace std;
#include "grader(13).cpp"
struct Arco
{
	int b, p;
};

struct Distanza
{
	int dist, peso, nd;
	
	bool operator <(const Distanza & other) const
	{
		if(dist != other.dist) return dist>other.dist;
		return peso >other.peso;
	}
};

vector<vector<Arco>> gr;
vector<bool> visited;

int Analizza(int N, int M, int s, int t, int arco_da[], int arco_a[], int capacita[], int R, int C)
{
	gr.resize(N+1);
	visited.resize(N+1, 0);
	for(int i=0; i<M; i++)
	{
		gr[arco_da[i]].push_back({arco_a[i], capacita[i]});
		gr[arco_a[i]].push_back({arco_da[i], capacita[i]});
	}
	
	priority_queue<Distanza> pq;
	pq.push({0,INT_MAX,s});
	
	while(!pq.empty())
	{
		int nd = pq.top().nd, dist = pq.top().dist, peso = pq.top().peso;
		pq.pop();
		
		if(visited[nd]) continue;
		visited[nd] = 1;

		if(nd == t)
			 return peso;
		
		for(auto u: gr[nd])
			pq.push({dist+1, min(peso, u.p), u.b});
	}
}

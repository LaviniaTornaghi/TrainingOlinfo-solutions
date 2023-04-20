#include <bits/stdc++.h>
using namespace std;
#define s N
#define t N+1
set<array<int,100>> check;
map<array<int, 100>, int> id;
vector<map<int,int>> gr;
vector<bool> part;
vector<bool> visited;
int conta =0; //id crescenti

void color(int nd, bool c=0)
{
	visited[nd] = 1;
	part[nd] = c;

	for(auto [u, b]:gr[nd])
		if(!visited[u])
			color(u, !c);
}

int main()
{
	int N, B, M;
	cin>>N>>M>>B;
	gr.resize(N+3); part.resize(N); visited.resize(N+3);

	for(int k=0; k<N; k++)
	{
		array<int, 100>a; fill(a.begin(), a.end(), 0);
		for(int i=0; i<M; i++) cin>>a[i];
		
		id[a] = conta++;

		for(int i=0; i<M; i++)
		{
			array<int, 100> b = a;
			
			for(int j=a[i]-1; j<=a[i]+1; j++)
			{
				if(j==a[i]) continue;
				b[i] = j;

				auto it = check.find(b);

				if(it!=check.end())
				{
					gr[conta-1][id[*it]] = 1;
					gr[id[*it]][conta-1] = 1;
				}	
			}
		}
		check.insert(a);
	}
	
	for(int i=0; i<N; i++)
		if(!visited[i]) color(i);
	
	for(int i=0; i<N; i++)
	{
		if(part[i])
		{
			for(auto it = gr[i].begin(); it!=gr[i].end(); it++)
				it->second = 0;
			gr[i][t] = 1;
		}
		else
			gr[s][i] = 1;
	}

	int flow = 0;
	
	vector<int> prv(N+3);
	while(true)
	{
		fill(prv.begin(), prv.end(), -1); 
		fill(visited.begin(), visited.end(), 0);

		stack<pair<int,int>> q;
		q.push({N, -1});

		while(!q.empty())
		{
			int nd=q.top().first, p = q.top().second;
			q.pop();
			visited[nd] = 1;
			prv[nd] = p;

			if(nd==t) break;

			for(auto [u, b] : gr[nd])
				if(b && !visited[u])
					q.push({u, nd});
		}
		if(!visited[t]) break;
		
		flow++;
		int nd = t;

		while(nd!=s)
		{
			gr[nd][prv[nd]] = 1;
			gr[prv[nd]][nd] = 0;
			nd = prv[nd];
		}
	}	
	cout<<flow;
}

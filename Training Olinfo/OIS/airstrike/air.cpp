#include <bits/stdc++.h>
using namespace std;

vector<map<int,bool>> gr;
vector<int>prv;
vector<bool> visited;
int N;

int main()
{
	cin>>N;
	gr.resize(2*N+2); //0 nodo di partenza 2*N +1 arrivo
	prv.resize(2*N+2); visited.resize(2*N+2);

	for(int i=0; i<N; i++)
	{
		int a, b;
		cin>>a>>b;
		gr[a][b+N] = 1;
	}

	for(int i=1; i<=N; i++) gr[0][i] = 1;
	for(int i=N+1; i<=2*N; i++) gr[i][2*N+1] = 1;

	int f = 0;

	while(true)
	{
		fill(prv.begin(), prv.end(), -1);
		fill(visited.begin(), visited.end(), 0);
		
		stack<pair<int,int>> q;
		q.push({0, -1});
		int nd, p;

		while(!q.empty())
		{
			nd = q.top().first; p = q.top().second;  q.pop();
			visited[nd] = 1;
			prv[nd] = p;	

			if(nd == 2*N +1) break;

			for(auto [u, b] : gr[nd])
				if(b && !visited[u])
				q.push({u, nd});
		}
		
		if(!visited[2*N+1]) break;
			
		nd = 2*N+1;
		f ++;

		while(nd!=0)
		{
			gr[nd][prv[nd]] = 1;
			gr[prv[nd]][nd] = 0;
			nd = prv[nd];

		}
	}
	cout<<f<<endl;
}

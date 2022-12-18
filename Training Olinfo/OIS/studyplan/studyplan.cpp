#include <bits/stdc++.h>

vector<vector<int>> gr;
vector<int> p;
int n;
int marca[100005];
int main()
{
	cin>>n;
	gr.resize(n+1);
	p.resize(n+1);
	
	p[n]= 0;	
	
	for(int i=0; i<n; i++) cin>>p[i];
	
	for(int i=0; i<n; i++)
	{
		int k, p;
		cin>>k;
		
		for(int j=0; j<k; j++)
		{
			cin>>p;
			marca[p] = 1;
			gr[i].push_back(p);
		}
	}
	deque <pair<int,int>> dq;	
	for(int i=0; i<n; i++) //tutti collegati al nodo n
	{
		if(marca[i]==0)
			dq.push_back({i,0});
	}
	
	int maxdist=0;
	vector<int> sol(n+1);
	while(!dq.empty())
	{
		int nd = dq.front().first, dist = dq.front().second;
		dq.pop_front();
		dist += p[nd]; //aggiungiamo il peso dell'arco di arrivo
		
		if(dist>maxdist) maxdist = dist;
		
		if(sol[nd]!=0 && dist<sol[nd]) continue;
		
		sol[nd] = dist;
			
		for(int i=0; i<gr[nd].size(); i++)
			dq.push_back({gr[nd][i], dist});
	}
	
	for(int i=0; i<n; i++) cout<<maxdist-sol[i]<<" ";
}

#include<bits/stdc++.h>
using namespace std;
#define ll long long

int N, M, T;
vector<vector<int>> gr;
vector<int> v;
int marca[100005];

struct Dist
{
	int nxtnd;
	ll dist;
	
	bool operator <(const Dist & other)const
	{
		return dist>other.dist;
	}
};

int pos(int t)
{
	return v[t%T];
}

int main()
{
	cin>>N>>M>>T;
	gr.resize(N); v.resize(T);
	while(M--)
	{
		int a, b;
		cin>>a>>b;
		gr[a].push_back(b);
		gr[b].push_back(a);
	}
	
	for(int i=0; i<T; i++)
		cin>>v[i];
	
	priority_queue<Dist> pq;
	pq.push({0,0});
	
	while(!pq.empty())
	{
		int nd = pq.top().nxtnd;
		ll dist = pq.top().dist;
		pq.pop();
		
		if(marca[nd]==1) continue;
		marca[nd] = 1;
		
		if(nd == N-1)
		{
			cout<<dist;
			exit(0);
		}
		
		int patrol = pos(dist+1);
		
		for(auto it : gr[nd])
		{
			if(it == patrol)
				pq.push({it, dist+2});
			else
				pq.push({it, dist+1});
		}
	}
}

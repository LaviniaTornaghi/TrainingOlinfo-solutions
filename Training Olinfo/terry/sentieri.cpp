#include <bits/stdc++.h>
using namespace std;

struct Arco
{
	int b;
	bool isbollente;
};

struct Dist
{
	int nd;
	int dist;
	
	bool operator <(const Dist & other)const
	{
		return dist>other.dist;
	}
};

vector<vector<Arco>> gr;
int marca[1005]; //5 in piu non fa mai male

int main()
{
	int N, A,B; //spiegato dal problema cosa sono
	cin>>N>>A>>B;
	gr.resize(N+1);
	
	for(int i=0; i<A; i++)
	{
		int a, b; //due estremi dell'arco, archi bidirezionali-> memorizzo da tutte e due le parti
		cin>>a>>b;
		gr[a].push_back({b,false});
		gr[b].push_back({a,false});
	}
	
	for(int i=0; i<B; i++)
	{
		int a,b;
		cin>>a>>b;
		gr[a].push_back({b,true});
		gr[b].push_back({a,true});
	}
	
	priority_queue<Dist> pq;
	pq.push({1,0});
	
	while(!pq.empty()) // ! è uguale a not
	{
		int nd = pq.top().nd;
		int dist = pq.top().dist;
		pq.pop();
		
		if(nd == N)
		{
			cout<<dist;
			return 0;
		}
		
		if(marca[nd]==true) continue;
		marca[nd] = true;
		
		for(int i=0; i<gr[nd].size(); i++)
		{
			int nxt = gr[nd][i].b;
			if(marca[nxt]==false)
			{
				if(gr[nd][i].isbollente == true)
					pq.push({nxt, dist +1});
				else
					pq.push({nxt, dist});
			}
		}
	}
}

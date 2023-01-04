#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Arco
{
	int b;
	int p;
};

struct Dist
{
	int ndarrivo;
	ll dist;
	int prev;
	
	bool operator <(const Dist & other)const
	{
		return dist > other.dist;
	}
};

vector<vector<Arco>> gr;
vector<ll> ds; //distance from start
vector<ll> de; //distance from end
vector<bool> isin; //apprtiene al percorso ottimale?
vector<int> p; //previous
int N, M;
vector<int> marca;

int main()
{
	cin>>N>>M;
	gr.resize(N); ds.resize(N, -1); de.resize(N, -1);
	isin.resize(N); p.resize(N); isin[0] = true; marca.resize(N);
	
	for(int i=0; i<M; i++) 
	{
		int a, b, p;
		cin>>a>>b>>p;
		gr[a].push_back({b,p});
		gr[b].push_back({a,p});
	}
	
	priority_queue<Dist> pq;
	pq.push({0,0, 0});
	//primo dijkstra: calcolo la distanza dal nodo 0 e mi salvo il precedente per riconoscere i nd nel path piu corto
	while(!pq.empty())
	{
		int nd = pq.top().ndarrivo, pr = pq.top().prev;
		ll dist = pq.top().dist;
		pq.pop();
		
		if(ds[nd]!=-1) continue;
		
		p[nd] = pr;
		ds[nd] = dist;
		
		for(int i=0; i<gr[nd].size(); i++)
			if(ds[gr[nd][i].b] == -1)
				pq.push({gr[nd][i].b, dist + gr[nd][i].p, nd});
	}
	//marco quali nodi apparatengono
	int nd = N-1;
	while(nd!=0)
	{
		isin[nd] = 1;
		nd = p[nd];
	}
	
	pq.push({N-1,0, N-1});
	//secondo dijkstra solo per salvare la distanza dal nodo N-1
	while(!pq.empty())
	{
		int nd = pq.top().ndarrivo;
		ll dist = pq.top().dist;
		pq.pop();
		
		if(de[nd]!=-1) continue;
		de[nd] = dist;
		
		for(int i=0; i<gr[nd].size(); i++)
			if(de[gr[nd][i].b] == -1)
				pq.push({gr[nd][i].b, dist + gr[nd][i].p, 0});
	}
	
	ll res = LLONG_MAX;
	pq.push({0, 0, 0});
	
	//terzo dijkstra, n.b. la distanza è in realtà il peso dell'arco in questione
	while(!pq.empty())
	{
		int nd = pq.top().ndarrivo, pq.top().prev;
		ll dist = pq.top().dist;
		pq.pop();

		if(marca[nd] == 0) //se non ho ancora visitato il nodo metto dentro gli archi che partono da lui
		{
			for(int i=0; i<gr[nd].size(); i++)
				pq.push({gr[nd][i].b, gr[nd][i].p, nd});
			marca[nd] = 1;
		}
		if(isin[nd] && isin[pr]) continue; //ma se entrambe i nd appartengono al path la coppia non è valida

		ll costo = ds[N-1] - (ds[pr] + de[nd]) -1; // a che val va decrementato
		//se il costo è negativo -> il percorso migliore dal nd di partenza + quello dal nodo di arrivo sono superiori al best path attuale quindi è inutile
		// -> se dist (peso arco)-costo è <= 0 allora l'arco dovrebbe avere val non positivo che non va bene
		if(costo >0 && (dist-costo)>0)
			res = min(res, dist-costo);
	}
	
	(res == LLONG_MAX) ? cout<<-1 : cout<<res;
}

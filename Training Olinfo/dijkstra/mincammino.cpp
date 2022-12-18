#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int dist[100005];
int marca[100005];

struct Arco
{
	int peso, ndarrivo;
};
vector <vector<Arco>> gr;

struct Dist
{
	int ndarrivo;
	int dist;
	
	bool operator <(const Dist & other)const
	{
		return dist>other.dist;
	}
};
void visita()
{
	priority_queue <Dist> pq;
	
	pq.push({0,0});
	
	while(!pq.empty())
	{
		Dist nodo = pq.top();
		pq.pop();
		
		if(marca[nodo.ndarrivo]!=0)
			continue;
		
		marca[nodo.ndarrivo] = 1;
		dist[nodo.ndarrivo] = nodo.dist;
		
		for(int i=0; i<gr[nodo.ndarrivo].size(); i++)
		{
			int nxt = gr[nodo.ndarrivo][i].ndarrivo;

			if(marca[nxt]!=1)
				pq.push({nxt, nodo.dist + gr[nodo.ndarrivo][i].peso});
		}
	}
}

void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<int> &D) 
{
    gr.resize(N);
	
	for(int i=0; i<M; i++)
		gr[X[i]].push_back({P[i], Y[i]});
	
	visita();
	
	for(int i=0; i<N; i++)
	{
		if(i!=0 and dist[i]==0)
			D[i] = -1;
		else
			D[i] = dist[i];
	}
}

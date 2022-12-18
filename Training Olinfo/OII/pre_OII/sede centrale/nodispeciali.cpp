#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#include "grader.cpp"

struct Nodo
{
	bool f;
	vector<pair<int,ll>> ar; //first = nxtnd, second = peso
	vector<pair<ll,int>> mem; //first = peso, second = nfliali
};

vector<Nodo> gr;

pair<ll, int> calcola(int nd, int prev)
{
	ll tot=0;
	int nf=0;
	for(int i=0; i<gr[nd].ar.size(); i++)
	{
		int nxt = gr[nd].ar[i].first;
		if(nxt!=prev)
		{
			if(gr[nd].mem[i].first  == -1)
				gr[nd].mem[i] = calcola(nxt, nd);
				
			tot += gr[nd].mem[i].first + gr[nd].ar[i].second * gr[nd].mem[i].second;
			nf += gr[nd].mem[i].second;
		}
	}
	if(gr[nd].f == true)
		nf ++;
	
	return {tot, nf};
}

int trova_sede(int N, int K, int A[], int B[], int P[], int filiali[])
{
    gr.resize(N+1);
    
    for(int i=0; i<K; i++) gr[filiali[i]].f = true;
    
    for(int i=0; i<N-1; i++) 
    {
		gr[A[i]].ar.push_back({B[i], P[i]});
		gr[B[i]].ar.push_back({A[i], P[i]});
		gr[A[i]].mem.push_back({-1, -1});
		gr[B[i]].mem.push_back({-1, -1});
	}
	
	ll mindist= LLONG_MAX;
	int pos;
	
	for(int i=1; i<=N; i++)
	{
		ll tmp = calcola(i, -1).first;
		
		if(tmp<mindist)
		{
			mindist = tmp;
			pos = i;
		}
	}
	return pos;
}

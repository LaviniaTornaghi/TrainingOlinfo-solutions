#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define in :
int N, M, Q, K;

struct NodoA
{
	vector<int> figli;
	vector<int> ndarrivo; //dove arriva la query
	vector<pair<int, ll>>query; //first = indice, second = esito
	vector<pair<int, ll>> archi; //first = dove arriva scond = peso
};

struct NodoB
{
	int padre;
	int ss; //size sottoalbero
	vector<int>figli;
};

struct FenwickTree
{
	vector<ll>tree;
	
	void add(int inx, int value)
	{
		for(++inx; inx<=M; inx += inx&(-inx))
			tree[inx] += value;
	}
	
	void addrange(int l, int r, int val)
	{
		add(l, val);
		add(r+1, -val);
	}
	
	ll query(int inx)
	{
		ll res=0; 
		for(++inx; inx>0; inx-= inx&(-inx))
		{
			res += tree[inx];
		}
		return res;
	}
};

FenwickTree ft;
vector<NodoA> A;
vector<NodoB>B;
int t=0;
vector<int>dfspos;

void computa(int nd)
{
	int size=0;
	dfspos[nd] = t++;

	for(auto it:B[nd].figli)
	{
		computa(it);
		size += B[it].ss;
	}
	B[nd].ss = 1 + size;
}

void dfs(int nd)
{
	for(auto arco in A[nd].archi)
		ft.addrange(dfspos[arco.first], dfspos[arco.first]+B[arco.first].ss-1, arco.second);
	
	
	for(int i=0; i<A[nd].query.size(); i++)
		A[nd].query[i].second = ft.query(dfspos[A[nd].ndarrivo[i]]);
	
	for(auto figlio in A[nd].figli) dfs(figlio);
	
	for(auto arco in A[nd].archi)
		ft.addrange(dfspos[arco.first], dfspos[arco.first]+B[arco.first].ss-1, -arco.second);
}

int main()
{
	cin>>N;
	A.resize(N+1);
	for(int i=2; i<=N; i++)
	{
		int tmp;
		cin>>tmp;
		A[tmp].figli.push_back(i);
	}
	
	cin>>M;
	B.resize(M+1); ft.tree.resize(M+1); dfspos.resize(M+1);
	for(int i=2; i<=M; i++) 
	{
		cin>>B[i].padre;
		B[B[i].padre].figli.push_back(i);
	}
	
	cin>>K;
	for(int i=0; i<K; i++)
	{
		int a, b, p;
		cin>>a>>b>>p;
		A[a].archi.push_back({b,p});
	}
	
	cin>>Q;
	for(int i=0; i<Q; i++)
	{
		int a, b;
		cin>>a>>b;
		A[a].ndarrivo.push_back(b);
		A[a].query.push_back({i, -1});
	}
	
	computa(1);
	dfs(1);
	
	vector<pair<int,ll>> res;
	
	for(int i=1; i<=N; i++) 
		for(int j=0; j<A[i].query.size(); j++)
			res.push_back(A[i].query[j]);
	
	sort(res.begin(), res.end());
	for(auto it : res) cout<<it.second<<endl;
}

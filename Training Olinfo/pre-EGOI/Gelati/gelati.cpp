#include<bits/stdc++.h>
#include<vector>

using namespace std;
int presta(int N, int C, vector <int> P)
{
	int i;
	int somma=0;
	int conta=0;

	sort(P.rbegin(),P.rend());
	
	for(i=0;i<P.size();i++)
	{
		somma=somma+P[i];
		conta=conta+1;
		
		if(somma>=C) break;
      	
	}
	return conta;
}

int main()
{
		int N, C;
		vector <int> P;
		cin>>N>>C;
		P.resize(N);
		for(int i=0; i<N; i++) cin>>P[i];
		cout<<presta(N,C, P);
}

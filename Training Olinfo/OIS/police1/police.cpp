#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

// input data
int N, K, i;
int V[MAXN + 1], marca[MAXN+1];

int main() {
  assert(2 == scanf("%d %d", &N, &K));
  for (i = 1; i <= N; i++) assert(1 == scanf("%d", &V[i]));
	
	if(K==1)  
	{
		cout<<0;
		return 0;
	}
	
	int conta = 1;
	int nd;
	nd = V[1];
	marca[1] = 1;
	while(true)
	{
		//cout<<nd<<endl;
		if(nd==K)
		{
			cout<<conta;
			return 0;
		}
		if(marca[nd]==1)
		{
			cout<<-1;
			return 0;
		}
		marca[nd] = 1;
		nd = V[nd];
		conta++;
	}
}

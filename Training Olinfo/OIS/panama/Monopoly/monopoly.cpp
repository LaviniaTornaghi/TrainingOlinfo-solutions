#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> V;

vector<vector<int>> migliore;



int main()
{
	cin>>N>>K;
	V.resize(N);
	migliore.resize(N);
	
	for(int i=0; i<N; i++)
	{
		cin>>V[i];
		
		migliore[i].resize(K * 3);
	}
	
	
	for(int j = 0, l = 2, r = 12; j < N; j++, r = (r+1)%N, l = (l+1)%N)
	{
		int min = V[l];
		
		for(int i = 1; i < 11; i++)
		{
			if(V[(l+i)%N] > min)
			{
				min = V[(l+i)%N];
			}
		}
		
		migliore[j][0] = min;
	}
	
	
	for(int i = 1; i < K; i++)
	{
		
		for(int j = 0, l = 2, r = 12; j < N; j++, r = (r+1)%N, l = (l+1)%N)
		{
			int min = V[l] + migliore[l][i-1];
			
			for(int ii = 1; ii < 11; ii++)
			{
				int idx = (ii+l)%N;
				if(V[idx] + migliore[idx][i-1] > min)
				{
					min = V[idx] + migliore[idx][i-1];
				}
			}
			
			migliore[j][i] = min;
		}
	}
	
	
	cout << migliore[0][K-1];
}

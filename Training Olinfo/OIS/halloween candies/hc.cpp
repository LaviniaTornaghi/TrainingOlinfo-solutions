#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	long long K;
	cin>>N>>K;
	vector<long long> v(N);
	long long sum=0;
	
	for(int i=0; i<N; i++)
	{
		cin>>v[i];
		sum += v[i];
	}
	
	if(K%sum==0)
		K = sum;
	else
		K %= sum;
	
	long long c = K;
	
	for(int i=0; i<N; i++)
	{
		c-= v[i];
		if(c<=0) 
		{
			cout<<i;
			break;
		}
	}
	
}

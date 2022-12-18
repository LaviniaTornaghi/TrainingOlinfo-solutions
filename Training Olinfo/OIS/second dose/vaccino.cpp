#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M; 
	cin>>N>>M;
	map<int, int> mp;
	
	for(int i=0; i<N; i++)
	{
		int n;
		cin>>n;
		mp[n]++;
	}
	long long res=0;
	for(int i=0; i<M; i++)
	{
		int n;
		cin>>n;
		if(mp.find(n)!=mp.end()) res++;
	}
	cout<<res;
}

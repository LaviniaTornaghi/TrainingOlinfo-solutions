#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, Q;
	cin>>N>>Q;
	vector<int> v(N), c(N, 0);
	for(int i=0; i<N; i++) cin>>v[i];
	
	long long res=0;
	while(Q--)
	{
		int i, p;
		cin>>i>>p;
		
		if((p + c[i])>v[i])
		{
			res += v[i]-c[i];
			c[i] = p;
		}
		else
			c[i] += p;
	}
	
	for(int i=0; i<N; i++) 
		if(c[i]>0) 
			res += v[i] - c[i];
			
	cout<<res;
}

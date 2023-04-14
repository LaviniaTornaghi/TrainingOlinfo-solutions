#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

int main()
{
	int N;
	cin>>N;
	vector<int>v(N), dp(N, 1);
	
	for(int i=0; i<N; i++) cin>>v[i];
	
	for(int i=1; i<N; i++)
	{
		if(i-v[i]-1>=0)
			dp[i]+=(dp[i-v[i]-1]%MOD);
		dp[i]+= (dp[i-1]%MOD);
		dp[i]%=MOD;
	}
	cout<<dp[N-1]+1<<endl;
}

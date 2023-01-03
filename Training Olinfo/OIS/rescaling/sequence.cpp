#include <bits/stdc++.h>
using namespace std;

vector<int>v;
vector<int> dp;
int N;

int main()
{
	cin>>N; v.resize(N); dp.resize(N, 1);
	for(int i=0;i<N; i++) cin>>v[i];
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<i; j++)
		{
			if(v[i]%v[j]==0 || v[i]<v[j])
				dp[i] = max(dp[i], dp[j]+1);
		}
	}
	for(auto it: dp) cout<<it<<" ";
	
	cout<<N -1 - *max_element(dp.begin(), dp.end());
}

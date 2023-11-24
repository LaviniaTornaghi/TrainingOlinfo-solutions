#include <bits/stdc++.h>
using namespace std;

int best_score(int N, int K, vector<int> &v)
{
	vector<int> ps (N+1); vector<int> dp(N); deque<int> dq;

	for(int i=1; i<=N; i++) ps[i] = ps[i-1] + v[i-1];
	
	for(int i=0; i<K; i++)
	{
		dp[i] = ps[i+1];
		dq.push_back(dp[i]);
	}

	for(int i= K; i<N; i++)
	{
		dp[i] = ps[i+1] - dq.front();

		if(dp[i-K] == dq.front()) dq.pop_front();

		while(!dq.empty())
		{
			if(dq.back() > dp[i]) 
				dq.pop_back();
			else
				break;
		}
		dq.push_back(dp[i]);
	}	

	return dp[N-1];
}


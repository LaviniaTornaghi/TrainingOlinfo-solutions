#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

ll res=1, N, K, n;

int main()
{
    cin>>N>>K;    
    vector<int> dp(N);

    for(int i=0; i<N;i++)
    {
        cin>>n;
        if(!n)
            res *= (K-dp[0]);
        else
        res*=(dp[n-1]-dp[n]);

        res%=MOD;
        dp[n]++;
    }
    cout<<res;
}

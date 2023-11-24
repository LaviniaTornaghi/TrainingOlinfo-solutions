#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
	float K, N, M;
	
	cin>>N>>M>>K;
	
	ll res = 0;
	ll tmp = ceil(N/K), tmp2 = ceil(M/K);
	res = tmp *tmp2;
	
	cout<<res;
}

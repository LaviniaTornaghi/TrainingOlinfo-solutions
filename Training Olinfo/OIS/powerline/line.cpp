#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin>>N;
	vector<int> v(N);
	for(auto& i:v) cin>>i;

	int res = 0;
	vector<int> days(N, 0);
	
	for(int i= N-2; i>=0; i--)
	{
		if(v[i]<v[i+1])
		{
			days[i] = 1 + days[i+1];
			res = max(days[i], res);
			v[i] = v[i+1];
		}
	}
	cout<<res<<endl;
}

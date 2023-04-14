#include <bits/stdc++.h>
using namespace std;

vector<int> v;
int N;

int dp(int i, int gr) //gr = gradazione max
{
	if(i>=N) return 0;
	if(i==N-1)
	{
		if(v[i]>=gr) return 1;
		else return 0;
	}
	
	if(gr<=v[i])
		return max(dp(i+1, gr), dp(i+2, max(gr,v[i])) +1);
	else
		return dp(i+1, gr);
}

int main()
{
	//ifstream cin("input.txt"); ofstream cout("output.txt");
	
	cin>>N;
	v.resize(N);
	for(int i=0; i<N; i++) cin>>v[i];
	
	cout<<dp(0, 0);
}

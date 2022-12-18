#include <bits/stdc++.h>
using namespace std;

void Colora(int N, int Q, vector <int> &A, vector <int> &B, vector <int> &C,
vector <int> &murale)
{
	for(int i=Q-1; i>=0; i--)
	{
		for(int j = A[i]; j<=B[i]; j++)
		{
			if(murale[j]==0)
				murale[j] = C[i];
		}
	}
}

int main()
{
	int q, n;
	vector<int> A, B, C, murale;
	cin>>n>>q;
	A.resize(q);
	B.resize(q);
	C.resize(q);
	murale.resize(n);
	for(int i=0; i<q; i++)
	{
		cin>>A[i]>>B[i]>>C[i];
	}
	Colora(n, q, A, B, C, murale);
	
	for(auto it:murale) cout<<it<<" ";
}

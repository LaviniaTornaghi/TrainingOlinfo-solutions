#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N; cin>>N; int conta=0;
	vector<int> v(N);
	for(auto& i:v) cin>>i;
	bool cond=false;
	while(cond==false)
	{
		cond=true;conta++;
		for(int i=0;i<N-1;i++)
		{
			if(v[i]<v[i+1])
			{
				cond=false;
				v[i]=v[i+1];
			}
		}

	}

	cout<<conta-1;

}

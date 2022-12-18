#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> gr;
int marca[10005];

map<pair<int,int>, bool> mp;

bool used(int a, int b)
{
	if(a>b)
	{
		a = a+b;
		b = a-b;
		a = a-b;
	}
	bool res = mp[{a,b}];
	mp[{a,b}] = true;
	//cout<<a<<" "<<b<<" "<<res<<endl;
	return res;
}

void dfs(int nd, int prev)
{
	if(marca[nd]==true) return;
	marca[nd] = true;
	
	//cout<<nd<<endl;
	
	for(int i=0; i<gr[nd].size(); i++)
	{
		if(gr[nd][i]!=prev)
		{
			if(!used(gr[nd][i], nd))
			{
				//cout<<"lol"<<endl;
				cout<<nd<<" "<<gr[nd][i]<<endl;
			}
			dfs(gr[nd][i], nd);
		}
	}
}

int main()
{
	int N, M;
	cin>>N>>M;
	gr.resize(N);
	for(int i=0; i<M; i++)
	{
		int a, b;
		cin>>a>>b;
		gr[a].push_back(b);
		gr[b].push_back(a);
		
		if(a>b)
		{
			a = a+b;
			b = a-b;
			a = a-b;
		}
		mp[{a,b}]=false;
	}
	dfs(0, -1);
}

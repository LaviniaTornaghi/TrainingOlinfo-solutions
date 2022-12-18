#include <iostream>
#include <vector>
#include <map>
using namespace std;

map <int, vector<int>> mp;

void inizia(int N, int M) 
{	
	for(int i=0; i<N; i++)
		mp[0].push_back(i);
	return;
}

void sposta(int a, int b) 
{
	mp[b].push_back(mp[a][mp[a].size()-1]);
	mp[a].pop_back();
}

int controlla(int a, int i) 
{
	//cout<<mp[a].size();
	if(mp[a].size()>i)
	{
		return mp[a][i];
		
	}
	return -1;
}

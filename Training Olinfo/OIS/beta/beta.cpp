#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N;
	vector<int> v;
	cin >>N;
	v.resize(N); 
	for(int i=0; i<v.size(); i++)
	  cin >>v[i];
	map<int, int> mp;
	int s=0;
	for(int i=0; i<v.size(); i++)
	{
		mp[v[i]]++;
	}
	for(auto item: mp)
	{
		if(mp[item.first]>=2)
		 s++;
	}
	
	if(s>=2)
	  cout <<"YES";
	 else
	   cout <<"NO";
		
	
}

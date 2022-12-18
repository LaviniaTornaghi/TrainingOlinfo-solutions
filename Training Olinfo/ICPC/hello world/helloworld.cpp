#include <bits/stdc++.h>
using namespace std;

int main()
{
	map <int, string> mp;
	
	mp[1803] = "gian";
	mp[1750] = "andrea";
	
	cout<<mp[1803]<<endl;
	
	for(auto item : mp) // item = un elemento della mappa
		cout<<item.first<<" "<<item.second<<endl;
	
	cout<<mp.size();
}

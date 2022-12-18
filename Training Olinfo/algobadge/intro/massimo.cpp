
#include <bits/stdc++.h>

using namespace std;

int trova_massimo(int N, vector <int> v)
{
	int max=-1500;
	int i;
	for(i=0; i<v.size(); i++)
	{
			if(v[i]>max)
			 max=v[i];	
	}
	return max;
	
}

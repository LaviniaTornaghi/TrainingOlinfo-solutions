#include<bits/stdc++.h>

using namespace std;

vector<int> v={'s', 'n', 'v', 'f', 'r', 'g', 'h', 'j', 'o', 'j', 'l', 'l', 'm', 'm', 'p', 'p', 'w', 't', 'd', 'y', 'i', 'b', 'e', 'c', 'u', 'x'};

int main()
{
	int n;
	char t[1000005];
	scanf("%d %s", &n, t);
	
	for(int i=0; i<n;i++)
	{
		t[i]=v[t[i]-97];
	}
	printf("%s", t);
}

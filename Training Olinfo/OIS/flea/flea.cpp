#include<bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	int pos=0;
	cin>>N;
	
	while(N--)
	{
		char ch;
		cin>>ch;
		if(ch=='L')
			pos--;
		else
			pos++;
	}
	cout<<abs(pos);
}

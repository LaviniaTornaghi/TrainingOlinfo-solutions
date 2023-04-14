#include<bits/stdc++.h>
using namespace std;

int N;

int main()
{
	stack<int> s;
	cin>>N;
	
	while(N--)
	{
		int n;
		cin>>n;
		
		while(!s.empty())
		{
			if(s.top()<n)
				s.pop() ;
			else
				break;
		}
		s.push(n);
	}
	cout<<s.size();
}

#include <string>
#include <iostream>
using namespace std;

string S;
long long TOT, tmp;

int main()
{
	cin>>S;
	for(int i=S.size()-1; i>=0; i--)
	{
		if(i>=4 && S[i]=='d')
		{
			if(S[i-1]=='l' && S[i-2]=='r' && S[i-3]=='o' && S[i-4]=='w')
			{
				tmp ++;
				i-=4;
			}
		}
		else if(i>=4 && S[i]=='o')
		{
			if(S[i-1]=='l' && S[i-2]=='l' && S[i-3]=='e' && S[i-4]=='h')
			{
				TOT += tmp;
				i-=4;
			}				
		}
	}
	
	cout<<TOT;
}

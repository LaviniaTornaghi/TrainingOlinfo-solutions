#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin>>T;
	
	for(int t=0; t<T; t++)
	{
		long long n1, n2;
		cin>>n1>>n2;
		
		if(n1<=0 && n2>=0) cout<<0<<endl;
		else
		{
			if(n1<0 && n2<0)
			{
				if((n2-n1)%2==0)cout<<'-'<<endl;
				else cout<<'+'<<endl;
				continue;
			}
			cout<<'+'<<endl;
		}
	}
}

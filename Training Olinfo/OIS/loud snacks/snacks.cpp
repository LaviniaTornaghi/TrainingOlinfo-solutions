#include<bits/stdc++.h>
using namespace std;

int main()
{
	int N, res= 0,R, i;
	cin>>N>>R;
	vector<int> v(N);
	for(int i=0; i<N; i++) cin>>v[i];
	sort(v.begin(), v.end());
	for(i=0; i<N-1; i++)
	{
		if(v[i] + v[i+1] <= R)
		{
			res ++;
			i++;
		}
		else 
			break;
	}
	res += (N-i);
	cout<<res<<endl;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int N, K;
    ll res=0;
    cin>>N>>K;
    vector <int> v(N); 
    
    for(int i=0; i<N; i++) cin>>v[i];
    
    for(int i=0; i<N-1; i++)
    {
        int l = -1, r=N;
        int k = v[i] + K;
        
        while(r-l>1) 
        {
			int mid = (l+r) /2;
			
			if(k < v[mid])
				r = mid;
			else
				l=mid;
		}
		
		if(v[l] == k) r--;
		res += r-1 -i;
	}
    cout<<res;
}

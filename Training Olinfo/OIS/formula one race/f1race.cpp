#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Info
{
	ll a, b, c;
	ll res, inx;
	void computa(ll t)
	{
		res= (t*t)*a + t*b + c;
	}
	bool operator <(const Info&other)const
	{
		if(res!=other.res) return res >other.res;
		return inx<other.inx;
	}
};

Info v[2005];
int N, q, p, t;

int main()
{
	cin>>N;
	
	for(int i=0; i<N; i++) 
	{
		cin>>v[i].a>>v[i].b>>v[i].c;
		v[i].inx = i+1;
	}
	cin>>Q;
	
	for(int i=0; i<Q; i++)
	{
		cin>>p>>t; p--;
		
		for(int j=0; j<N; j++) v[j].computa(t);
		
		nth_element(v, v+p, v+N);
		cout<<v[p].inx<<endl;
	}
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

vector<ll> v;
map<int, int> mp;
int N;

struct FT
{
	vector<ll> ft;
	int s;
	void init(int size)
	{
		s= size;
		ft.resize(size+1, 0);
	}
	
	ll query(int qe)
	{
		qe ++;
		ll res = 0;
		
		while(qe>0)
		{
			res += ft[qe]%MOD;
			res = res %MOD;
			qe -= qe & (-qe);
		}
		return res;
	}
	void add(ll value, int inx)
	{
		inx++;
		
		while(inx<=s)
		{
			ft[inx] += value;
			ft[inx] %= MOD; 
			inx += inx & (-inx);
		}
	}
};

FT ft;

int main()
{
	cin>>N;
	v.resize(N);

	for(int i=0; i<N; i++)
	{
		int n;
		cin>>n;
		v[i] = n;
		mp[n]++;
	}
	int i=0;
	for(auto it = mp.begin(); it!=mp.end(); it++)
		it->second = i++;
		
	ft.init(mp.size());
	ll tot = 0;
	for(int i=0; i<N; i++)
	{
		int n= v[i];
		ll tmp = ft.query(mp[n]-1);
		tot += tmp+1;
		tot %=MOD;
		//cout<<n<<" "<<tmp<<endl;
		
		ft.add(tmp+1, mp[n]);
	}
	cout<<tot<<endl;
}


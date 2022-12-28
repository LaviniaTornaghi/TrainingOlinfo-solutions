#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, L;
unordered_map<string,ll> mp;

int lyndon_word(string a, int n)
{
  int i = 0, j = 1, k;
  while (j < n) {
    for (k = 0; k < n && a[(i+k)%n] == a[(j+k)%n]; k++);
    if (a[(i+k)%n] <= a[(j+k)%n]) {
      j += k+1;
    } else {
      i += k+1;
      if (i < j)
        i = j++;
      else
        j = i+1;
    }
  }
  return i;
}

int main()
{
	scanf("%d %d", &N, &L);
	ll res=0;
	string tmp;
	
	for(int i=0; i<N; i++)
	{
		string tmp;
		 cin>>tmp;
		 int start = lyndon_word(tmp,L);
		 string key;
		 for(int j=start; j<L; j++)key+=tmp[j];
		 for(int j=0; j<start; j++) key+= tmp[j];
//		 cout<<key<<" "<<mp[key]<<endl;
		 res += mp[key];
		 mp[key]++;
	 }
	
	printf("%lld", res);
}

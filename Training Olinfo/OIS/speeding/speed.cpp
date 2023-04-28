#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long

int main()
{
    int N;
    cin>>N;
    vector<int>a(N), b(N);

    for(auto &i:a) cin>>i;
    for(auto &i:b) cin>>i;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    int s = 0, n=0; ll res=1;
    for(int i=0; i<N; i++)
    {
        for(int j=s; j<N; j++)
        {
            if(b[j]<=a[i])
            {
                n++;
                s++;
            }
            else break;
        }
        res = (res*(n--))%MOD;
    }
    cout<<res;
}

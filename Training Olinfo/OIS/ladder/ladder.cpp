#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, res=0; cin>>N;
    vector<int>v(N+1);
    for(int i=1; i<=N; i++) cin>>v[i];
    
    for(int i=1;i<=N; i++)
        res = max(res, v[i]-v[i-1]);

    cout<<res;
}

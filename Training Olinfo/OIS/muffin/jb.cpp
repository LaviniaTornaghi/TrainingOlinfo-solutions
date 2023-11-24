#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, K; cin>>N>>K;
    vector<int> v(N);
    for(auto& i: v) cin>>i;
    int res = INT_MIN, tmp = 0;

    for(int i=0; i<K; i++) tmp += v[i];
    res = tmp;
    for(int i=K; i<N; i++){
        tmp += v[i];
        tmp -= v[i-K];
        res =max(res, tmp);
    }
    cout<<res;
}

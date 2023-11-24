#include<bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> dsu;
vector<array<ll, 3>> e; //edges

int find(int a){
    if(dsu[a] == a) return a;
    return dsu[a] = find(dsu[a]);
}

bool join(int a, int b){
    a = find(a); b=find(b);
    if(a==b) return false;
    dsu[b] = a;
    return 1;
}

int progetta(int N, int M, int K, vector<int> &A, vector<int> &B, vector<int> &W){
    for(int i=0; i<M; i++) e.push_back({W[i], A[i]-1, B[i]-1});
    sort(e.begin(), e.end()); reverse(e.begin(), e.end());
    dsu.resize(N); iota(dsu.begin(), dsu.end(), 0);

    int c = N-K, sum = 0;

    for(auto [w, a, b]:e){
        if(!join(a,b)) continue;
        sum += w; c--;
        if(!c) break;
    }
    return sum;
}

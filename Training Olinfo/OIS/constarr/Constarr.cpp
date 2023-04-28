#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long

int N, M, L, R, K;
vector<ll> c; //choices for each value of mod

vector<ll> mult(vector<ll> &a, vector<ll>&b)
{
    vector<ll> res(M);
    
    for(int j=0; j<M; j++)
        for(int k=0; k<M; k++)
        {
            int j2 = (j-k+M);
            if(j2>=M) j2-=M;
                res[j] +=  a[j2]* b[k];
                res[j]  %= MOD;
        }
    return res;
}

vector<ll> fastexp(vector<ll> C, ll length)
{
    if(length == 1) return c;

    vector<ll>a = fastexp(C, length/2);

vector<ll> ris = mult(a, a);

    if(length%2) ris = mult(ris, C);

    return ris;
}

int main()
{
    cin>>N>>M>>L>>R>>K;

    int left = L - L%M;
    int right = R - R%M;
    c.resize(M);
    for(int i=0; i<M; i++)
    {
        int ub = right +i;
        if(ub>R) ub-=M;
        int lb = left + i;
        if(lb<L) lb += M;

        c[i] = (ub-lb+M) / M;
    }
   
   vector<ll> ans = fastexp(c, N);
   cout<<ans[K];
}


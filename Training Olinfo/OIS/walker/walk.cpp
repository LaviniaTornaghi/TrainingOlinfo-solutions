#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 666013
#define matrix vector<array<ll, 2>>

ll N, K;

matrix  matmult(matrix  a, matrix  b)
{
    matrix  res(2);

    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            for(int k=0; k<2; k++)
            {
                res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= MOD;
            }

    return res;
}

matrix fastexp(matrix  b, ll  exp)
{
    if(exp == 0)
        return {{1,0}, {0,1}};    

    if(exp == 1)
        return b;
    
    matrix a = fastexp(b, exp/2);
    matrix res = matmult(a, a);
    
    if(exp%2) res = matmult(res, b);

    return res;
}
int main()
{
    cin>>N>>K;
    matrix z = {{0, N-1}, {1, N-2}};

    matrix ris = fastexp(z, K);

    cout<<ris[0][0];
}

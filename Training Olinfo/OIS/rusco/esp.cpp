#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, M;
vector<bool> visited;
vector<ll> dp;
vector<ll> prv;
vector<ll> peso;
vector<array<int, 3>>  A; //0= arco verso la copia, 1 arco verso dx o sx, 2 arco o verso l'lato o verso il basso

ll spfa()
{
    fill(dp.begin(), dp.end(),-1);
    fill(visited.begin(), visited.end(),0);
    
    dp[1] = 0;
    queue<int> q;
    q.push(1);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        visited[v] = 0;
        
        //crea lista di adiacenza
        vector<pair<int,int>> gr;

        if(v%2) // nodo archi uscenti
        {
            //arco verso altra versione di se stesso
            gr.push_back({v-1, A[v][0]});
            //arco verso destra
            if(A[v][1] != -1) gr.push_back({v-1+2, A[v][1]});
            //arco verso giu
            if(A[v][2] != -1) gr.push_back({v-1+2*M, A[v][2]});
        }
        else
        {
            //arco verso altra versione di se stesso
            gr.push_back({v+1, A[v][0]});
            //arco verso sinistra
            if(A[v][1] != -1) gr.push_back({v-2+1, A[v][1]});
            //arco verso su
            if(A[v][2] != -1) gr.push_back({v-2*M+1, A[v][2]});

        }

        for(auto [u, b] : gr)
        {
            if(!b) continue;
            int costo = 0;
            if( v == u+1) // vado da uscente ad entrante
                costo = -peso[u];
            else if(v == u-1)
                costo = peso[v];

            if(dp[u] < dp[v] + costo)
            {
                if(!visited[u])
                    q.push(u);
                visited[u] = 1;
                prv[u] = v;
                dp[u] =  dp[v] + costo;
            }
        }
    }   
    return dp[2*(M*(N-1) + M-1)];
}

int main()
{
    cin>>N>>M;
    dp.resize(2*M*N+1);
    visited.resize(2*N*M+1);
    prv.resize(2*N*M+1);
    A.resize(2*N*M+1);
    peso.resize(2*N*M+1);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            int a; cin>>a;
            int node = 2*(M*i + j); 
            peso[node] = a;
            //archi entranti
            A[node][0] = 1;
            //archi uscenti
            A[node+1][1] = A[node+1][2] = 1;
            //corner case
            if(i==N-1) A[node+1][2] = -1;
            if(j==M-1) A[node+1][1] = -1;
            if(i==0) A[node][2] = -1;
            if(j==0) A[node][1] = -1;
       }       
    }

    ll flow = 0, costo = 0;
    
    while(flow<2)
    {
        costo += spfa();
        flow ++;
        int nd = 2*(M*(N-1)+M-1); 

        while(nd != 1)
        {
            if(nd%2) //archi uscenti
            {
                if(prv[nd] == nd-1)//altra copia di se stesso
                {
                    A[nd][0] = 1;
                    A[prv[nd]][0] = 0;
                }
                else if(prv[nd] == nd-1+2*M) //arrivo da sotto
                {
                    A[nd][2] = 1;
                    A[prv[nd]][2] = 0;
                }
                else //arrivo da dx
                {
                    A[nd][1] = 1;
                    A[prv[nd]][1] = 0;
                }
            }
            else
            {
                if(prv[nd]==nd+1)
                {
                    A[nd][0] = 1;
                    A[prv[nd]][0] = 0;
                }
                else if(prv[nd] == nd - 2*M+1)
                {
                    A[nd][2] = 1;
                    A[prv[nd]][2] = 0;
                }
                else
                {
                    A[nd][1] = 1;
                    A[prv[nd]][1] = 0;
                }
            }
            nd = prv[nd];
        }
   }
   cout<<costo;
}

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> gr;
vector<bool> visited;
vector<int> prv, mn;
int N;
int f=0, delta;

void flow(int nd, int p=-1)
{
	visited[nd] = 1;
	prv[nd] = p;

//	cout<<nd<<" "<<p<<endl;
//	cout<<"minimo "<<mn[nd]<<endl;	
	if(nd == N+1) return;

	for(int i=0; i<=N+1; i++)
	{
		if(gr[nd][i]  && !visited[i])
		{
			mn[i] = min(mn[nd], gr[nd][i]);
			flow(i, nd);
		}
	}

}

int main()
{
	cin>>N;
	gr.resize(N+2, vector<int>(N+2)); // 0 = rubinetto N+1 = pozzo
	prv.resize(N+2); visited.resize(N+2); mn.resize(N+2);

	for(int i=1; i<=N; i++)
	{
		int a;
		cin>>a;
		gr[0][i] = a;
	}
	

	for(int i=1; i<=N; i++)
	{
		int b;
		cin>>b;
		gr[i][N+1] = b;
	}

	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			int c; cin>>c;

			if(i!=j)
				gr[i][j] = c;
		}
		
	}

	while(true)
	{
		fill(prv.begin(), prv.end(), -1);
		fill(visited.begin(), visited.end(), 0);
		fill(mn.begin(), mn.end(), INT_MAX);
		
		int nd = 0, p = -1, mnx;

		queue<array<int, 3>> q;
		q.push({0, -1, INT_MAX});

		while(!q.empty())
		{
			nd = q.front()[0]; p = q.front()[1]; mnx = q.front()[2];  q.pop();
			visited[nd] = 1;
			prv[nd] = p;
			if(nd == N+1) break;

        		for(int i=0; i<=N+1; i++)		
	        	{
        	        	if(gr[nd][i]  && !visited[i])
                		{
                        		q.push({i, nd, min(mnx, gr[nd][i])});
                		}
			}
		}

		if(prv[N+1]==-1) break;
		
		delta = mnx;

		f += delta;
		
//		cout<<f<<endl;
		nd = N+1;
	
	//	for(auto it : prv) cout<<it<<" ";
	//	cout<<endl;

		while(nd!=0)
		{
			gr[nd][prv[nd]] += delta;
			gr[prv[nd]][nd] -= delta;
			nd = prv[nd];
		}
	}

	cout<<f;
}

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<deque>


using namespace std;

struct Punto
{
	int r, c;
};

vector<Punto>mtx[1005][1005];
int isNode[1005][1005];
int isVisited[1005][1005];
int N, M;
Punto nord, sud, ovest, est;
int contaloop=0;
struct Arco
{
	Punto start;
	Punto end;
};
void VisitaDfs(Punto root)
{
	deque<Arco>dq;
	isVisited[root.r][root.c] = 1;
	// inserisco tutti gli archi della root nella coda 
	for(int i=0; i<mtx[root.r][root.c].size(); i++)
	{
		Arco arco;
		arco.start = root;
		arco.end = mtx[root.r][root.c][i];
		dq.push_front(arco);

	}
	while(!dq.empty())
	{
		Arco arco;
		arco = dq[0];
		dq.pop_front();
		Punto nodo = arco.end;
		if(isVisited[nodo.r][nodo.c] == 1)
		{
			//cout << "esiste un problema";
			continue;
		}	
		isVisited[nodo.r][nodo.c] = 1;
		// esamino tutti i nodi adiacenti di nodo
		for(int i=0; i<mtx[nodo.r][nodo.c].size();i++)
		{
			// controllo se e l'arco di partenza
			Punto nodo2 = mtx[nodo.r][nodo.c][i];
			if(arco.start.r == nodo2.r and arco.start.c == nodo2.c)
			{
				continue;
			}
			if(isVisited[nodo2.r][nodo2.c] == 1)
			{
				// e un loop
				contaloop++;
				continue;
			}
			Arco arco2;
			arco2.start = nodo;
			arco2.end = nodo2;
			dq.push_front(arco2);
			
		}
		
	}
}

int main()
{
	int i, j, r, c;
	cin>>N>>M;
	for(i=0; i<N; i++)
	{
		string s;
		cin>>s;
		for(j=0; j<M; j++)
		{
			int r1, c1, r2, c2;
			r1 = i;
			r2 = i+1;
			if(s[j] == '\\')
			{
				c1 = j;
				c2 = j+1;
			}
			else 
			{
				c1 = j+1;
				c2 = j;
			}
			Punto pt1 = {r1, c1};
			Punto pt2 = {r2, c2};
			mtx[r1][c1].push_back(pt2);
			mtx[r2][c2].push_back(pt1);
			isNode[r1][c1] = 1;
			isNode[r2][c2] = 1;
			
		}
	}
	//dichiaro i 4 nodi cardinali
	 nord = {N+1, 0};
	 sud = {N+1, 1};
	 ovest = {N+1, 2};
	 est = {N+1, 3};
	
	// aggiungo i 4 vertici del rettangolo
	
	isNode[0][0] = 1;
	isNode[0][M] = 1;
	isNode[N][0] = 1;
	isNode[N][M] = 1;
	
	isNode[N+1][0] = 1;
	isNode[N+1][1] = 1;
	isNode[N+1][2] = 1;
	isNode[N+1][3] = 1;
	
	//aggancio tutti i nodi del lato nord
	r=0;
	for(c=0; c<=M; c++)
	{
		if(isNode[r][c]==1)
		{
			Punto pt = {r, c};
			mtx[nord.r][nord.c].push_back(pt);
			mtx[r][c].push_back(nord); 
		}
	}
	
	//aggancio tutti i nodi del lato sud
	r=N;
	for(c=0; c<=M; c++)
	{
		if(isNode[r][c]==1)
		{
			Punto pt = {r, c};
			mtx[sud.r][sud.c].push_back(pt); 
			mtx[r][c].push_back(sud); 
		}
	}
	
	//aggancio tutti i nodi del lato ovest
	c=0;
	for(r=0; r<=N; r++)
	{
		if(isNode[r][c]==1)
		{
			Punto pt = {r, c};
			mtx[ovest.r][ovest.c].push_back(pt);
			mtx[r][c].push_back(ovest); 
		}
	}
	
	//aggancio tutti i nodi del lato est
	c=M;
	for(r=0; r<=N; r++)
	{
		if(isNode[r][c]==1)
		{
			Punto pt = {r, c};
			mtx[est.r][est.c].push_back(pt);
			mtx[r][c].push_back(est); 
		}
	}
	// visito il grafo
	VisitaDfs(nord);
	for(r=0; r<=N; r++)
	{
		for(c=0; c<=M; c++)
		{
			if(isNode[r][c] == 1)
			{
				if(isVisited[r][c] == 0)
				{
					Punto pt = {r,c};
					VisitaDfs(pt);
				}
			}
		}
	}
	cout << contaloop <<endl;
}

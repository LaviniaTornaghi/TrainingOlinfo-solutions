#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005

struct Nodo
{
	int padre;
	int heavych;
	int beauty;
	vector<int> figli;
	int subsize; //subtree size
};

vector<Nodo> tr;
vector<int> dfs;
vector<int>posdfs; //memorizzo per ogni nodo in che posizione � nella dfs
vector<int>foglie;
vector<int> solution;
int m[MAXN]; //marcatura dei label
vector<int> reset;


int Dfsorder(int nd)
{
	posdfs[nd] = dfs.size();
	dfs.push_back(nd);
	
	if (tr[nd].figli.size()==0)
	{
		tr[nd].heavych = -1;
		tr[nd].subsize = 1;
		foglie.push_back(nd);
		return 1;
	}
	
	tr[nd].subsize =1; //lui stesso
	int max=0, heavych;

	for(int i=0; i<tr[nd].figli.size(); i++)
	{
		int son = tr[nd].figli[i];
		int sizeson = Dfsorder(son);
		tr[nd].subsize+=sizeson;
		
		if(sizeson>max)
		{
			max = sizeson;
			heavych = tr[nd].figli[i];
		}
	}
	tr[nd].heavych = heavych;
	
	return tr[nd].subsize;
}

int massimo, actualwindow, sxfinestra;
int valmassimo, position, sxattuale; // position � dxattuale

void vcatena(int nd)
{
	sxfinestra = posdfs[nd]; 
	actualwindow ++;
	m[tr[nd].beauty]++;
	
	if(m[tr[nd].beauty] == 1)
		reset.push_back(tr[nd].beauty);
	
	if(m[tr[nd].beauty]>massimo || (m[tr[nd].beauty]==massimo && tr[nd].beauty<valmassimo))
	{
		massimo = m[tr[nd].beauty];
		valmassimo = tr[nd].beauty;
	}

	//allarghiamo finestra a sinistra
	while(sxfinestra<sxattuale-1)
	{
		sxattuale--;
		
		int belact = tr[dfs[sxattuale]].beauty;
		m[belact]++;
		
		if(m[belact] == 1)
			reset.push_back(belact);
		
		if(m[belact]>massimo || (m[belact]==massimo && belact<valmassimo))
		{
			massimo = m[belact];
			valmassimo = belact;
		}
		actualwindow++;
	}
	sxattuale = sxfinestra;
	//allarghiamo la finestra a destra
	while(actualwindow<tr[nd].subsize)
	{
		position ++;		
		int belact = tr[dfs[position]].beauty;
		m[belact]++;
		
		if(m[belact] == 1)
			reset.push_back(belact);
		
		if(m[belact]>massimo || (m[belact]==massimo && belact<valmassimo))
		{
			massimo = m[belact];
			valmassimo = belact;
		}
		actualwindow++;
	}
	
	solution[nd] = valmassimo;
	
	//chiamata ricorsiva di risalita
	int ndpadre = tr[nd].padre;	
	if(tr[ndpadre].heavych == nd && tr[nd].padre != -1)	
		vcatena(ndpadre);
}

void visit(int nd)
{
	solution[nd] = tr[nd].beauty;
	
	if(tr[tr[nd].padre].heavych!=nd) // se la foglia non appartiene ad una catena	
		return;
	
	//siamo in una catena, faccio partire la risalita
	massimo=0; actualwindow=0; sxfinestra, position = posdfs[nd];
	valmassimo=1000005;
	sxattuale = posdfs[nd];
	
	vcatena(nd);
	
	for(int i=0; i<reset.size(); i++)
		m[reset[i]] = 0;
	
	reset.clear();
}

vector<int> solve(int n, vector<int> p, vector<int> z)
{
	//inizializzazioni
	posdfs.resize(n);
	tr.resize(n);
	solution.resize(n);
	
	tr[0].beauty = z[0];
	posdfs[0] = 0;
	tr[0].padre = -1;
	
	for(int i=1; i<n; i++)
	{		
		tr[p[i]].figli.push_back(i);
		tr[i].padre = p[i];
		tr[i].beauty = z[i];	
	}
	
	//determinare ordine di dfs
	Dfsorder(0);	
	
	//visita di tutte le foglie
	for(int i=0; i<foglie.size(); i++)
		visit(foglie[i]);

	return solution;
}

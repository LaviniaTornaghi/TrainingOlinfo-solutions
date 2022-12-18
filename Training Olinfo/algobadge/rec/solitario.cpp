#include <iostream>
#include <vector>
#include<fstream>
using namespace std;

int N,M;
int ris = 0;
vector<vector<int>> ri;
vector<vector<int>> co;
vector<vector<int>> d1;
vector<vector<int>> d2;

bool in(int r, int c)
{
	return (r>=0 && r<N && c>=0 && c<M);
}

void ric(int r, int c, int tmp)
{	/*
	cout<<r<<" "<<c<<" tmp "<<tmp<<endl;
	
	cout<<"righe\n";
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
			cout<<ri[i][j]<<" ";
		
		cout<<endl;
	}
	cout<<"colonne\n";
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
			cout<<co[i][j]<<" ";
		
		cout<<endl;
	}
	cout<<"d1\n";
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
			cout<<d1[i][j]<<" ";
		
		cout<<endl;
	}
	cout<<"d2\n";
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
			cout<<d2[i][j]<<" ";
		
		cout<<endl;
	}*/
	

	
	// uscita
	if(r==(N))
	{
		
		ris = max(ris, tmp);
		
		//cout<<"risultato "<<ris<<endl;
		
		return;
	}
	
	if(((N*M)-((r)*M+c)+tmp) <ris)
		return;	
	
	int nc, nr;
	
	if(c==M-1)
	{
		nc=0;
		nr = r +1;
	}
	else
	{
		nc = c+1;
		nr = r;
	}
	
	//cout<<"nuove "<<nr<<" "<<nc<<endl;
	
	bool istris=false;
	
	if(in(r, c-1) && ri[r][c-1]>=2)
		istris = true;
	if(in(r-1, c) && co[r-1][c]>=2)
		istris = true;
	if(in(r-1, c-1) && d1[r-1][c-1]>=2)
		istris = true;
	if(in(r-1, c+1) && d2[r-1][c+1]>=2)
		istris = true;
	

	
	if(!istris)
	{
		
		if(in(r, c-1))
			ri[r][c] = ri[r][c-1] + 1;
		else
			ri[r][c] = 1;
		
		if(in(r-1, c))
			co[r][c] = co[r-1][c]+1;
		else
			co[r][c] = 1;
		
		if(in(r-1, c-1))
			d1[r][c] = d1[r-1][c-1] + 1;
		else
			d1[r][c] = 1;
		
		if(in(r-1, c+1))
			d2[r][c] = d2[r-1][c+1] +1;
		else
			d2[r][c]=1;
		
		ric(nr,nc, tmp +1);
	}
	
	ri[r][c] = 0;
	co[r][c] = 0;
	d1[r][c] = 0;
	d2[r][c] = 0;
	
	ric(nr, nc, tmp);
}

int main()
{
	FILE *fr, *fw;

	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");
	
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");
	fscanf(fr, "%d %d", &N, &M);


	ri.resize(N, vector<int>(M,0));
	co.resize(N, vector<int>(M,0));
	d1.resize(N, vector<int>(M,0));
	d2.resize(N, vector<int>(M,0));
	
	ric(0, 0, 0);	

	fprintf(fw, "%d\n", ris);
	fclose(fr);
	fclose(fw);
}

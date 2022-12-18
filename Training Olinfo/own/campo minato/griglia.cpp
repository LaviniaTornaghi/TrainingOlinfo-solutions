#include <bits/stdc++.h>
using namespace std;

int m[105][105];
bool valid[105][105];
int N, M;

void visita(int r, int c)
{
	if(m[r][c]!=-1) return;
	if(valid[r][c]==false) m[r][c] = 0;
	
	if(c==M-1 && r==N-1)
	{
		m[r][c] = 1;
		return;
	}
	if(c==M-1)
	{
		if(m[r+1][c]==-1)
		{
			visita(r+1, c);
		}
		m[r][c] = m[r+1][c];	
		return;
	}
	if(r==N-1)
	{
		if(m[r][c+1]==-1)visita(r, c+1);
		m[r][c] = m[r][c+1];
		return;
	}
	if(m[r+1][c] == -1) visita(r+1,c);
	if(m[r][c+1] == -1) visita(r, c+1);
	m[r][c] = m[r+1][c] + m[r][c+1];
}

int main()
{

	cin>>N>>M;
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			m[i][j] = -1;
			char ch;
			cin>>ch;
			if(ch=='+') m[i][j] = 0;
			else valid[i][j] = true;
		}
	}
	visita(0,0);
	
	cout<<m[0][0];
}


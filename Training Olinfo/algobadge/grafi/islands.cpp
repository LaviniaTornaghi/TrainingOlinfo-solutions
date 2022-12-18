#include <iostream>
#include <deque>
using namespace std;

struct Cella
{
	int r, c;
};

int m[1005][1005];

int R, C, N; //numero celle di terra

Cella vicini[4] =
{
	{0,1}, {1,0}, {-1, 0}, {0,-1}
};

bool checkcella (Cella c)
{
	if(c.r<0 or c.r >= R)
		return false;
		
	if(c.c <0 or c.c>=C)
		return false;
		
	if(m[c.r][c.c]!=1)
		return false;
		
	return true;
}

void marcaterritorio(Cella c)
{
	deque <Cella> dq;
	
	dq.push_back(c);
	
	while(!dq.empty())
	{
		Cella c1 = dq.front();
		
		dq.pop_front();
		
		if(m[c1.r][c1.c]!=1)
			continue;
			
		m[c1.r][c1.c]=2;
		
		for(int i=0; i<4; i++)
		{
			Cella c2 = c1;
			c2.r += vicini[i].r;
			c2.c += vicini[i].c;
			
			if(checkcella(c2))
				dq.push_back(c2);
		}
	}
}

Cella cercapenisola()
{
	Cella cella = {-1, -1};
	int r, c;
	
	r=0;
	for(int c=0; c<C; c++)
	{
		if(m[r][c]==1)
		{
			cella.r = r;
			cella.c = c;
			return cella;
		}
	}
	
	r = R-1;
	for(int c=0; c<C; c++)
	{
		if(m[r][c]==1)
		{
			cella.r = r;
			cella.c = c;
			return cella;
		}
	}
	
	c=0;
	
	for(int r=0; r<R; r++)
	{
		if(m[r][c]==1)
		{
			cella.r = r;
			cella.c = c;
			return cella;
		}
	}
	
	c=C-1;
		
	for(int r=0; r<R; r++)
	{
		if(m[r][c]==1)
		{
			cella.r = r;
			cella.c = c;
			return cella;
		}
	}
	
	return cella;
}

Cella cercaisola (int r0)
{
	int r, c;
	Cella cella = {-1, -1};
	
	for(r=r0; r<R-1; r++)
	{
		for(c=1; c<C-1; c++)
		{
			if(m[r][c] == 1)
			{
				cella.r = r;
				cella.c = c;
				
				return cella;
			}
		}
	}
	return cella;
}

int main()
{
	cin>>R>>C;
	
	int r,c;
	
	for( r=0; r<R; r++)
	{
		for(c = 0; c<C; c++)
		{
			cin>>m[r][c];
		}
	}
	
	while(true)
	{
		Cella cella = cercapenisola();
		
		if(cella.r == -1)
			break;
			
		marcaterritorio(cella);
	}
	
	int conta = 0;
	Cella cella = {1,1};
	while(true)
	{
		 cella = cercaisola(cella.r);
		
		if(cella.r == -1)
			break;
		
		conta ++;
			
		marcaterritorio(cella);
	}	
	
	cout<< conta;
}

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int NN;

struct FT
{
	int *tree;
	int N;
	long long swap;
	
	void init(int *T)
	{
		tree = T;
		N=0;
		swap = 0;
	}
	
	void add(int value)
	{
		N++;
		value ++;
		
		while(value <= NN)
		{
			tree[value]++;
			
			value += value & (-value);
		}
	}
	
	void count(int qe)
	{
		int sum = 0;
		qe++;
		
		while(qe>0)
		{
			sum += tree[qe];
			
			qe -= qe & (-qe);
		}
		
		swap += N - sum;
	}
};

int *T1;
int *T2;

FT tr[2];

long long int paletta_sort(int N, int* V)
{
	for(int i=0; i<N; i++)
	{
		if(i%2==0)
		{
			if(V[i]%2!= 0)
				return -1;
		}
		else
			if(V[i]%2 == 0)
				return -1;
		
		V[i]/= 2;
	}
	
	NN=N;	
	T1 = (int*)malloc((N+1)*sizeof(int));
	T2 = (int*)malloc((N+1)*sizeof(int));
	
	memset(T1,0,(N+1)*sizeof(int));
	memset(T2,0,( N+1)*sizeof(int));

	tr[0].init(T1);
	tr[1].init(T2);
	
	for(int i=0; i<N-1; i+=2)
	{
		tr[0].count(V[i]);
		tr[0].add(V[i]);
		
		tr[1].count(V[i+1]);
		tr[1].add(V[i+1]);
	}
	if(N%2==1)
		tr[0].count(V[N-1]);
	
	return tr[0].swap + tr[1].swap;
}

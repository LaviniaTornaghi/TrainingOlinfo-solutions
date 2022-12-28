#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 1000005
#include "grader.cpp"

int mem[MAXN];

vector <int> S, A, B;
int NN;

int hmin(int n, int maxh)
{
	if(mem[n]!= 0)
		return max(mem[n], maxh);
	
	if(n == NN -1 or n + B[n]>=NN)
	{
		mem[n] = S[n];
		return max(maxh, S[n]);
	}
		
	
	int minimo=MAXN;
	int tmp;
	vector <int> v(B[n]-A[n]+1);

	for(int i =0, j=A[n] + n; j<=(B[n] + n); j++, i++)
	{
		v[i] = j;
	}
	sort(v.begin(), v.end());
	
	for(int i=0; i<v.size(); i++)
	{
		if(v[i]<NN and S[v[i]]<=minimo)
		{
			tmp = hmin(v[i],S[n]);
		}
	
		if(tmp<minimo)
			minimo = tmp;
	}
	
	mem[n] = minimo;
	return max(minimo, maxh);
}

int salta(int N, vector<int> s, vector<int> a, vector<int> b)
{
	S = s;
	A = a;
	B = b;
	NN = N;
	
	if(N==1)
		return S[0];
	
	return hmin(0, S[0]);
}

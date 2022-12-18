#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
using namespace std;

int tempo_massimo(int N, int a[], int b[])
{
    int m[N][3];
	
	m[N-1][0] = 0;
	m[N-1][1] = a[N-1];
	m[N-1][2] = b[N-1];
	
	for(int i=N-2; i>=0; i--)
	{
		m[i][0] = max(m[i+1][0],max(m[i+1][1], m[i+1][2]));
		m[i][1] = max(m[i+1][0], m[i+1][1]) + a[i];
		m[i][2] = max(m[i+1][0], m[i+1][1]) + b[i];		
	}	
	return max(m[0][0], max(m[0][1], m[0][2]));
}

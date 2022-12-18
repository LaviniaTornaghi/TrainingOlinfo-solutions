#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 100000

int N, i, sum;
int V[MAXN];

int main() 
{
    FILE *fr, *fw;
    vector <int> v;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
	
    for(i=0; i<N; i++)
	{
		assert(1 == fscanf(fr, "%d", &V[i]));
		
		sum += V[i];
		
		if(V[i]<0)
			v.push_back(V[i]);
	}
	sort(v.begin(),v.end());
	
	i=0; 
	
	while(sum<=0)
	{
		sum += -(v[i]*2);
		i++;
	}       

    fprintf(fw, "%d\n", i);
    fclose(fr);
    fclose(fw);
    return 0;
}

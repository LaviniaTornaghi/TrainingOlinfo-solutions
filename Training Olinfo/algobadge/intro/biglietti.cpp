#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

int compra(int N, int M, int A, int B) 
{
	int prezzo=0;

	if(A*M<B)
		return A*N;
	
	prezzo = B*(N/M);
	N=N%M;
	
	if(A*N<B)
		prezzo += A*N;
	else
		prezzo += B;
			
	return prezzo;
}

int main() {
    FILE *fr, *fw;
  	int N, M, A, B;  

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(4 == fscanf(fr, "%d%d%d%d", &N, &M, &A, &B));

    fprintf(fw, "%d\n", compra(N, M, A, B));
    fclose(fr);
    fclose(fw);
    return 0;

/*	cin>>N>>M>>A>>B;
	cout<<compra(N,M,A,B);*/
	
}

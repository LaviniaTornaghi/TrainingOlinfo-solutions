#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

// #define DEBUG 1

using namespace std;
int N;  // N = Numero Portate
int K;  // peso portate

const int OVER_SIZE = 1000000001;
int portate[5000];

// La matrice memo contiene le soluzioni dei sottoproblemi
int memo[5001][5001] = {0};

int mangia_rec(int i, int peso) 
{
    if (peso < 0) return 0;

    if (memo[i][peso] > 0)
        return memo[i][peso];

    if ( i == 0)
    {
        if (peso - portate[i]> 0)    
            memo[i][peso] = OVER_SIZE;
        // prendendo portate[0] supero la soglia ---> quindi prendo la portata
        else
            memo[i][peso] = portate[i];
        return memo[i][peso];                   
    }
    
    //=================================
    // (1) Non prendo questa portata;
    //=================================
    int costo1 = mangia_rec(i-1, peso);
    
    //=================================
    // (2)Prendo questa portata;
    //=================================
    int costo2;
    
    // Con questa portata stò superando il limite K, 
    // prendo la portata e mi fermo qui con la ricorsione
    if (peso -portate[i] <= 0)   // Ho superato il limite K 
    {  
        costo2 = portate[i];
    }    
    else
        costo2 = mangia_rec(i-1, peso -portate[i]) + portate[i];

    // Calcola ricorsivamente la soluzione e la memorizza in memo[i][j]
    return memo[i][peso] = min(costo1, costo2);
 }


int dump(int N, int K)
{
    for (int i = 0; i < N; i++)
    {    
        for (int j = 0; j <= K; j++)
            cout << memo[i][j] <<"  ";

        cout << endl;
    }
}    

 int main()
 {

#ifdef DEBUG
    ifstream cin("input5.txt");  // Leggo Da File
    // Cout - non voglio sovrascriverlo

#else    
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif
    cin >> N >> K;
    for (int i=0; i<N; i++)
        cin >> portate[i];

    int costo = mangia_rec(N-1, K);
    cout << costo << endl;
    
#ifdef DEBUG
    dump(N, K);
#endif
    return 0;
}
 

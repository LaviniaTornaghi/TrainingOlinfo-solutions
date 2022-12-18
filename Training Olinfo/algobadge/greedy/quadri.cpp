#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

bool checkWindow(int wSize, int * v, long long M, int N) // wsize è almeno pari a 2
{
    int i;
    int first = 0;
    int last = wSize-1;
    bool ris = true;
    long long windowsSum = 0;
    for (i=0; i<wSize; i++)
        windowsSum += v[i];
    if (windowsSum > M)
        return false; 
    for (i=wSize; i<N; i++)
    {
        windowsSum -= v[first];
        windowsSum += v[last+1];
        first++;
        last++;
        if (windowsSum > M)
            return false;
    }    
    return true;
}


int quadri(int N, long long M, int* v)
{
    int i;
    int max = 0;
    long long somma=0;
    
    for (i=0; i<N; i++)
    {    
        if (v[i] > max)
            max = v[i];
        somma += max;
    }
    // Corner Case 1 - c'è' almeno un elemento maggiore del massimale
    if (max >= M) 
    {
        return 0; // con questo corner case lo chiudiamo qui.
    }
    // Corner Case 2 - la somma di tutti i quadri è inferiore al massimale
    if (somma < M) 
    {
        return N; // con questo corner case lo chiudiamo qui.
    }
   
    long long Wlower, Wupper;
    Wlower = 1;  // con Windows size = 1 sappiamo che funziona
    Wupper = 2;  // Wupper è da provare
    while (true)
    {
        bool ris = checkWindow(Wupper, v, M, N);
        
        if (ris == false)
            break;
        Wlower = Wupper;
        Wupper = 2*Wupper;
        if (Wupper > N)
        {    
            Wupper = N;
            break;
        }    
    }
    while (Wupper - Wlower > 1)
    {
        int distance = Wupper - Wlower;
        
        // tentiamo a meta'
        bool ris = checkWindow(Wlower + distance/2, v, M, N);
        if (ris == true)
            Wlower = Wlower + distance/2;
        else
            Wupper = Wlower + distance/2;
    }
    return (Wlower);
}

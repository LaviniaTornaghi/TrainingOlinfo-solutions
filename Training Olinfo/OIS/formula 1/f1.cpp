#include <bits/stdc++.h>
using namespace std;
#define printH cout<<"Hamilton"<<endl;
#define printV cout<<"Verstappen"<<endl;

int N;
vector<int> H, V;

int main() 
{
    cin >> N;
    H.resize(N);
    for (int i = 0; i < N; i++)
        cin >> H[i];
    V.resize(N);
    for (int i = 0; i < N; i++)
        cin >> V[i];
     
    if(accumulate(H.begin(), H.end(), 0)<accumulate(V.begin(), V.end(), 0))
        printH
    else
        printV
    
    int fh = *min_element(H.begin(), H.end()), fv = *min_element(V.begin(), V.end());
    
    if(fh<fv)
        printH
    else
        printV
    
    return 0;
}

#include <iostream>
#include <stdio.h>
using namespace std;

int N;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> N;

    double ris = 0;
    double incr = 0;

    if (N==1)
        ris = 0 / 2; // 0
    else if (N == 2)
        ris = 1 / 2.0; // 0.5
    else if (N == 3)
        ris = 3 / 2.0; // 1.5
    else
    {
        ris = (double)N * (double)(N - 1) / 2.0;
        ris /= 2.0;
    }
    cout << ris << endl;
}

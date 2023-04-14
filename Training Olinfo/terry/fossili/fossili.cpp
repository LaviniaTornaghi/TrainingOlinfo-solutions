#include <bits/stdc++.h>
using namespace std;

ofstream off("output.txt");

void solve(int t) {
    int a1, a2, b1, b2, c1, c2;
    cin >> a1 >> a2;
    cin >> b1 >> b2;
    cin >> c1 >> c2;

	
	
    int risposta = max(0, min({a2,b2,c2}) - max({a1,b1,c1}));

    off << "Case #" << t << ": " << risposta << "\n";
}

int main() 
{
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}

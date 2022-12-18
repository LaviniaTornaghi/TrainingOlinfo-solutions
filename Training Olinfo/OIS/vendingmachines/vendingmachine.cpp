// NOTE: it is recommended to use this even if you don't understand the
// following code.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N, Q;
        cin >> N >> Q;
        bool hacker = false;
        int L;
        int tot=0;
        vector<int> P(N);
        for (int i = 0; i < N; i++) {
            cin >> P[i];
        }
        for (int i = 0; i < Q; i++) {
            cin >> L;
            if(L<0) tot -= P[-L -1];
            else
				tot += L;
				
			if(tot<0)hacker = true;
        }


        // insert your code here
       


        // print the result
        if (hacker) {
            cout << "HACKER" << endl;
        } else {
            cout << "OK" << endl;
        }
    }
}

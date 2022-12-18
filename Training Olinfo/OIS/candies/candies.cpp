
// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> S(N);
    map<int, int> mp;
    for (int i = 0; i < N; i++) {
		int x;
        cin >> x;
        mp[x]++;
    }
	
	int tot=0;
	int i=0;
	for(auto item : mp)
	{
		i++;
		tot+=(i*item.second);
	}
	cout<<tot<<endl;
    return 0;
}

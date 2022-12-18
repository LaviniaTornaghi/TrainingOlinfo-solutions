#include <iostream>
#include <map>
using namespace std;

map<long long int,int> mp;

void aggiungi(long long int id) {
    mp[id]++;
}

void togli(long long int id) {
    mp[id]--;
}

int conta(long long int id) {
    
    if(mp.find(id)!=mp.end())
        return mp[id];
        
    return 0;
}


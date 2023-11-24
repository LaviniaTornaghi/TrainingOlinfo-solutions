#include <bits/stdc++.h>
using namespace std;
#include "grader.cpp"

set<long long> p;
set<long long> n;

void inizia() {
    return;
}

void apri(long long v) {
    p.insert(v);
    n.insert(-v);
}

void chiudi(long long v) {
    p.erase(v);
    n.erase(-v);
}

long long chiedi(long long v) 
{
    auto rp = (p.lower_bound(v));
    auto rn = (n.lower_bound(-v));
    
    if(rp == p.end() && rn == n.end())
		return -1;
	if(rp == p.end())
		return -(*rn);
	if(rn == n.end())
		return (*rp);
    
    if(*rp-v < v+*rn)
		return *rp;
	else if(*rp-v == v+*rn)
		return *rp;
	return -(*rn);
}

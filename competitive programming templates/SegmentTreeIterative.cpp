#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
const int lim = 500005;
int n, st[lim * 4];

void upd(int ps, int val){
	for(st[ps += n] = val; ps /= 2;)
		st[ps] = st[ps * 2] + st[ps * 2 + 1];
}

int que(int lf, int rg){ //[lf, rg)
	int rsA = 0, rsB = 0;
	for(lf += n, rg += n; lf < rg; lf /= 2, rg /= 2){
		if(lf & 1) rsA += st[lf ++];
		if(rg & 1) rsB += st[-- rg];
	}
	return rsA + rsB;
}
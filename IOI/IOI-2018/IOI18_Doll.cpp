#include "doll.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> c, x, y, desti, state, l, r;
int id = 0, sz = 0;

int build(int nd, int tri){
	if(tri == 0) return -1;
	if(nd == 1) return id++;

	int nw = - sz - 1; sz ++;
	l[-nw] = build(nd/2, tri - min(nd/2, tri));
	r[-nw] = build(nd/2, min(nd/2, tri));

	return nw;
}

int dfs(int nw){
	if(nw >= 0) return nw;
	state[-nw] = 1 - state[-nw];
	if(state[-nw]) return dfs(l[-nw]);
	else return dfs(r[-nw]);
}

void create_circuit(int m, vector<int> a){
	a.push_back(0);

	int k = 1;
	for(; k < a.size(); k *= 2);
	
	l.resize(k); r.resize(k); state.resize(k);
	build(k, a.size());

	c.assign(m + 1, -1);
	desti.resize(2 * id);
	x.resize(sz); y.resize(sz);

	for(int i = 0; i < a.size(); i++)
		desti[dfs(-1)] = a[i];

	for(int i = 1; i <= sz; i++){
		x[i - 1] = l[i];
		y[i - 1] = r[i];
		if(x[i - 1] >= 0) x[i - 1] = desti[x[i - 1]];
		if(y[i - 1] >= 0) y[i - 1] = desti[y[i - 1]];
	}

	answer(c, x, y);
}
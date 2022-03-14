#include <iostream>
#include <vector>
using namespace std;

const int LG = 17;
const int MX = (1 << 17) + 5;

int n, fwt[MX], ans[MX], par[MX], ac[MX], last[MX];

int find(int nw){
	if(ac[nw]) return nw;
	return par[nw] = find(par[nw]);
}

void upd(int ps, int v){
	for(; ps < MX; ps += ps & -ps)
		fwt[ps] += v;
}

void range_upd(int lf, int rg){
	while((lf = find(par[lf])) <= rg){
		ac[lf] = 0;
		upd(lf, -1);
	}
}

int get(int v){
	int rs = 0, id = 0;
	for(int i = LG - 1; i >= 0; i --){
		if(id + (1 << i) <= n && rs + fwt[id + (1 << i)] < v){
			id += (1 << i); rs += fwt[id];
		}
	}
	return id + 1;
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E){
	n = N;

	for(int i = 1; i < n; i ++)
		if(K[i - 1] > R) last[i] = i;
		else last[i] = last[i - 1];
	last[n] = last[n - 1];

	for(int i = 1; i <= n; i ++)
		par[i] = i + 1;

	for(int i = 1; i < MX; i ++){
		upd(i, 1);
		ac[i] = 1;
	}

	for(int i = 0; i < C; i ++){
		S[i] = get(S[i] + 1);
		E[i] = find(par[get(E[i] + 1)]) - 1;
		range_upd(S[i], E[i]);
		if(last[E[i] - 1] < S[i]){
			ans[S[i]] ++; ans[E[i] + 1] --;
		}
	}

	int id = 1;
	for(int i = 1; i < MX; i ++){
		ans[i] += ans[i - 1];
		if(ans[i] > ans[id]) id = i;
	}

	return id - 1;
}
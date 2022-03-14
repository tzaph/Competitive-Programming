#include "werewolf.h"
#include <vector>
using namespace std;

#define vi vector<int>
const int MXN = 200005;
const int LG = 18;

vector<int> g[MXN];
vector<int> dsuTree[MXN][2];
int dsu[MXN], n;
int id[MXN][2], tin[MXN][2], tout[MXN][2], tim = 0, anc[MXN][LG][2];
int fwt[MXN];

int find(int nw){
	if(dsu[nw] == nw) return nw;
	return dsu[nw] = find(dsu[nw]);
}

void join(int u, int v, int tp){
	int fu = find(u), fv = find(v);
	if(fu != fv){
		dsu[fv] = fu;
		dsuTree[fu][tp].push_back(fv);
	}
}

void dfs(int nw, int bf, int tp){
	anc[nw][0][tp] = bf;
	for(int i = 1; i < LG; i ++)
		anc[nw][i][tp] = anc[anc[nw][i - 1][tp]][i - 1][tp];
	tin[nw][tp] = ++ tim;
	id[tim][tp] = nw;
	for(int nx : dsuTree[nw][tp])
		dfs(nx, nw, tp);
	tout[nw][tp] = tim;
}

void upd(int nw, int v = 1){
	for(; nw < MXN; nw += nw & -nw)
		fwt[nw] += v;
}

int que(int nw){
	int rs = 0;
	for(; nw > 0; nw -= nw & -nw)
		rs += fwt[nw];
	return rs;
}

struct queries{
	int lf, rg, id, val;
	queries(){lf = rg = id = val = 0;}
	queries(int a, int b, int c, int d){
		lf = a; rg = b; id = c; val = d;
	}
};

vector<queries> qq[MXN];

vi check_validity(int n, vi X, vi Y, vi S, vi E, vi L, vi R){
	for(int i = 0; i < X.size(); i ++){
		g[X[i]].push_back(Y[i]);
		g[Y[i]].push_back(X[i]);
	}

	for(int i = 0; i < n; i ++) dsu[i] = i;
    for(int nw = 0; nw < n; nw ++)
		for(int nx : g[nw])
			if(nx < nw) join(nw, nx, 1);

	for(int i = 0; i < n; i ++) dsu[i] = i;
	for(int nw = n - 1; nw >= 0; nw --)
		for(int nx : g[nw])
			if(nx > nw) join(nw, nx, 0);

	tim = 0; dfs(0, 0, 0);
	tim = 0; dfs(n - 1, n - 1, 1);

	int q = S.size();
	vector<int> ans(q, 0);

	for(int i = 0; i < q; i ++){
		int s = S[i], e = E[i];
		for(int j = LG - 1; j >= 0; j --){
			if(L[i] <= anc[s][j][0]) s = anc[s][j][0];
			if(anc[e][j][1] <= R[i]) e = anc[e][j][1];
		}
		qq[tin[s][0] - 1].push_back(queries(tin[e][1], tout[e][1], i, -1));
		qq[tout[s][0]].push_back(queries(tin[e][1], tout[e][1], i, 1));
	}

	for(int i = 1; i <= n; i ++){
		upd(tin[id[i][0]][1]);
		for(auto c : qq[i])
			ans[c.id] += c.val * (que(c.rg) - que(c.lf - 1));
	}

	for(int i = 0; i < q; i ++)
		ans[i] = ans[i] > 0;
	return ans;
}
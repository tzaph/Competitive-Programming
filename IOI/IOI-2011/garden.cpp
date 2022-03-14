#include "garden.h"
#include <vector>
#include <bitset>
using namespace std;

const int inf = 1e9 + 69;
int n, m, p, mn1[150005], mn2[150005];
vector<int> in[300005]; int out[300005];
vector<int> ans1, ans2;
bitset<300005> vis;

void dfs(int nw, int dst, vector<int> &ans, int &res, int dest){
	if(vis[nw]){
		if(nw == dest) res = dst;
		return;
	}
	vis[nw] = 1;
	if(nw < n) ans[dst] ++;
	for(int nx : in[nw])
		dfs(nx, dst + 1, ans, res, dest);
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]){
	n = N; m = M; p = P;
	for(int i = 0; i < n; i ++)
		mn1[i] = mn2[i] = -1;
	for(int i = 0; i < m; i ++){
		if(mn1[R[i][0]] == -1) mn1[R[i][0]] = R[i][1];
		else if(mn2[R[i][0]] == -1) mn2[R[i][0]] = R[i][1];
		if(mn1[R[i][1]] == -1) mn1[R[i][1]] = R[i][0];
		else if(mn2[R[i][1]] == -1) mn2[R[i][1]] = R[i][0];
	}

	for(int i = 0; i < n; i ++)
		if(mn2[i] == -1) mn2[i] = mn1[i];

	for(int i = 0; i < 2 * n; i ++){
		int nx;
		if(i < n) nx = mn1[i];
		else nx = mn2[i % n];
		if(i % n == mn1[nx]) nx += n;

		out[i] = nx;
		in[nx].push_back(i);
	}

	int rs1 = inf, rs2 = inf;
	ans1.assign(2 * n + 5, 0); ans2.assign(2 * n + 5, 0);
	vis = 0;
	dfs(p, 0, ans1, rs1, p);
	vis = 0;
	dfs(p + n, 0, ans2, rs2, p + n);

	for(int i = 0; i < Q; i ++){
		int ans = 0;
		for(int j = G[i] % rs1; j <= min(G[i], N); j += rs1)
			ans += ans1[j];
		for(int j = G[i] % rs2; j <= min(G[i], N); j += rs2)
			ans += ans2[j];
		answer(ans);
	}

	return;
}
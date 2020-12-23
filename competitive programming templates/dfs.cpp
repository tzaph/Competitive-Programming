#include <iostream>
#include <vector>
using namespace std;
const int N = 100005;
const int LOGN = 18;

int n;
vector<int> adj[N];
int depth[N], sz[N], par[N];
int anc[N][LOGN];
void dfs(int nw, int bf){
	sz[nw] = 1;
	par[nw] = bf;
	for(int nx : adj[nw]) if(nx != bf){
		depth[nx] = depth[nw] + 1;
		dfs(nx, nw);
		sz[nw] += sz[nx];
	}
}

void build_lca(){
	for(int i = 1; i <= n; i ++)
		anc[i][0] = par[i];
	for(int j = 1; j < LOGN; j ++)
		for(int i = 1; i <= n; i ++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
}

int lca(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
	for(int i = LOGN - 1; i >= 0; i --)
		if(diff & (1 << i)) u = anc[u][i];
	if(u == v) return u;
	for(int i = LOGN - 1; i >= 0; i --)
		if(anc[u][i] != anc[v][i])
			u = anc[u][i], v = anc[v][i];
	
}
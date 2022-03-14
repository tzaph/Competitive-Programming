#include "race.h"
#include <vector>
#include <bitset>
using namespace std;

vector<pair<int, int> > adj[200005];
int dp[1000005], path[1000005], sz[200005];
int n, k, ans = -1, centroid, mxnode, cnt = 0;
bitset<200005> vis;

int dfs_subtree(int nw, int bf){
	sz[nw] = 1;
	for(pair<int, int> nx : adj[nw])
		if(!vis[nx.first] && nx.first != bf)
			sz[nw] += dfs_subtree(nx.first, nw);
	return sz[nw];
}

void centroid_decomp(int nw, int bf, int all){
	int rs = all - sz[nw];
	for(pair<int, int> nx : adj[nw]) 
		if(!vis[nx.first] && nx.first != bf){
			centroid_decomp(nx.first, nw, all);
			rs = max(rs, sz[nx.first]);
		}
	if(rs < mxnode){
		centroid = nw;
		mxnode = rs;
	}
}

void dfs(int nw, int bf, int cst, int edge, bool fill){
	if(cst > k) return;
	if(!fill){
		if(dp[k - cst] == cnt && (edge + path[k - cst] < ans || ans == -1))
			ans = edge + path[k - cst];
		if(cst == k && (edge < ans || ans == -1))
			ans = edge;
	}else if(dp[cst] < cnt  || edge < path[cst]){
		dp[cst] = cnt;
		path[cst] = edge;
	}

	for(pair<int, int> nx : adj[nw]) if(!vis[nx.first] && nx.first != bf)
		dfs(nx.first, nw, cst + nx.second, edge + 1, fill);
}

void solve(int nw){
	cnt ++;
	if(dfs_subtree(nw, -1) <= 1) return;
	mxnode = sz[nw] + 1;
	centroid_decomp(nw, -1, sz[nw]);
	for(pair<int, int> nx : adj[centroid]) if(!vis[nx.first]){
		dfs(nx.first, centroid, nx.second, 1, false);
		dfs(nx.first, centroid, nx.second, 1, true);
	}
	vis[centroid] = 1;
	for(pair<int, int> nx : adj[centroid]) if(!vis[nx.first])
		solve(nx.first);
}

int best_path(int N, int K, int H[][2], int L[]){
	n = N; k = K;
	for(int i = 1; i < n; i ++){
		adj[H[i - 1][0]].push_back({H[i - 1][1], L[i - 1]});
		adj[H[i - 1][1]].push_back({H[i - 1][0], L[i - 1]});
	}

	solve(0);
	return ans;
}

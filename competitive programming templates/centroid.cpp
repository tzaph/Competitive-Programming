#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5 + 5;

int sz[MX];
vector<int> adj[MX];
bitset<MX> used;

void dfs_sz(int nw, int bf){
	sz[nw] = 1;
	for(int nx : adj[nw]) if(nx != bf && !used[nx]){
		dfs_sz(nx, nw);
		sz[nw] += sz[nx];
	}
}

int get_centroid(int nw){
	dfs_sz(nw, nw);

	int szt = sz[nw] / 2;
	for(bool f = 0; !f;){
		f = 1;
		for(int nx : adj[nw]) if(!used[nx] && sz[nx] <= sz[nw])
			if(sz[nx] > szt / 2){
				f = 0;
				nw = nx; break;
			}
	}

	return nw;
}

void solve(int nw = 1){
	nw = get_centroid(nw);

	// do stuff

	used[nw] = 1;
	for(int nx : adj[nw]) if(!used[nx])
		solve(nx);
}
#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5 + 5;

/* Code for scc and bridge tree */
int n, m, par[MX], tin[MX], low[MX], tim = 0;
vector<int> adj[MX], bt[MX];
int scc_id[MX];
set<pair<int, int> > bridges;
vector<int> articulation_point; // not needed
void dfs(int nw){
	tin[nw] = low[nw] = ++ tim;
	for(int nx : adj[nw]){
		if(!tin[nx]){
			par[nx] = nw;
			dfs(nx);
			if(low[nx] > tin[nw])
				bridges.insert({nw, nx});
			if(low[nx] >= tin[nw])
				articulation_point.push_back(nw);
			low[nw] = min(low[nw], low[nx]);
		}else if(nx != par[nw])
			low[nw] = min(low[nw], tin[nx]);
	}
}
void create_scc(int nw, int sccid){
	scc_id[nw] = sccid;
	for(int nx : adj[nw])
		if(!bridges.count({nw, nx}) && !scc_id[nx])
			create_scc(nx, sccid);
}
/* note
bridge tree can be made from block cut
by adding new vertices for each edge and connect (u, x) (x, v)
where x is the edge number (+ n for offset)
so technically this is kinda useless
*/
void construct_bridge_tree(){
	for(int i = 1; i <= n; i ++)
		if(!tin[i]) dfs(i);
	int cnt_scc = 0;
	for(int i = 1; i <= n; i ++)
		if(!scc_id[i]) create_scc(i, ++ cnt_scc);
	for(auto i : bridges){
		int u = scc_id[i.first], v = scc_id[i.second];
		bt[u].push_back(v);
		bt[v].push_back(u);
	}
	// bt is bridge tree
}
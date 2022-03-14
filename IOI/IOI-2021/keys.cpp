#include "keys.h"
#include <bits/stdc++.h>
using namespace std;

const int MX = 300005;

struct disjointSet{
	int par[MX];
	void init(){
		for(int i = 0; i < MX; i ++)
			par[i] = i;
	}

	int f(int x){
		return par[x] = (par[x] == x ? x : f(par[x]));
	}

	int uni(int u, int v){
		u = f(u); v = f(v);
		if(u == v) return 0;

		par[u] = v;
		return 1;
	}
} dsu;

int n, m;
vector<pair<int, int> > adj[MX];
int last[MX];
bitset<MX> vis, dead, havekey;
vector<int> locked[MX], reach, clear_locked;

int mn = MX;
vector<int> ans;

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c){
	n = r.size(); m = c.size();
	dsu.init();

	for(int i = 0; i < m; i ++){
		adj[u[i]].push_back({v[i], c[i]});
		adj[v[i]].push_back({u[i], c[i]});
	}

	for(int it = 1; ; it ++){ // idea of boruvka's algo, each iter kills half of the graph
		vis = 0;
		bool merge = 0;

		for(int i = 0; i < n; i ++)
			if(dsu.f(i) == i && !dead[i] && last[i] != it){
				merge = 1;

				last[i] = it;
				queue<int> bfs;
				bfs.push(i);

				bool upd = 1;

				for(int nw; bfs.size();){
					nw = bfs.front();
					bfs.pop();

					if(dsu.f(nw) != dsu.f(i)){
						dsu.par[dsu.f(i)] = dsu.f(nw);
						last[dsu.f(nw)] = it;
						upd = 0;
						break;
					}

					if(vis[nw]) continue;
					vis[nw] = 1;
					reach.push_back(nw);

					if(!havekey[r[nw]]){
						havekey[r[nw]] = 1;
						for(; locked[r[nw]].size(); locked[r[nw]].pop_back())
							bfs.push(locked[r[nw]].back());
					}

					for(pair<int, int> nx : adj[nw])
						if(havekey[nx.second])
							bfs.push(nx.first);
						else{
							clear_locked.push_back(nx.second);
							locked[nx.second].push_back(nx.first);
						}
				}

				if(upd){
					dead[i] = 1;

					if(reach.size() < mn){
						ans = reach;
						mn = reach.size();
					}else if(reach.size() == mn){
						for(int x : reach)
							ans.push_back(x);
					}
				}

				havekey = 0;
				for(int x : clear_locked)
					locked[x].clear();
				reach.clear();
				clear_locked.clear();
			}

		if(!merge) break;
	}

	vector<int> z(n, 0);
	for(int i : ans)
		z[i] = 1;
	return z;
}
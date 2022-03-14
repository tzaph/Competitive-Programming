#include <iostream>
#include <vector>
using namespace std;

const int MX = 1000005;
int n;
vector<int> adj[MX];
bool stage = 0;
// stage = 0 if no deg > 2
// stage = 1 otherwise 
	// -> we focus on 4 vertices: the current vertex that has deg = 3
	// and the 3 other neighbouring vertices

struct dsu{
	int par[MX], sz[MX], deg[MX], rt;
	vector<int> cyc;
	bool valid = 1;

	void init(int r = -1){
		rt = r;
		for(int i = 0; i < MX; i ++){
			par[i] = i;
			deg[i] = 0;
			sz[i] = 1;
		}
	}

	int find(int x){
		if(par[x] == x) return x;
		return par[x] = find(par[x]);
	}

	void uni(int a, int b){
		if(a == rt || b == rt) return;
		deg[a] ++; deg[b] ++;
		if(deg[a] > 2 || deg[b] > 2) valid = 0;

		a = find(a), b = find(b);
		if(a == b) valid = 0, cyc.push_back(a);
		else par[a] = b, sz[b] += sz[a];
	}
} s[5]; // 0 is default, 1 - 4 for rest

void Init(int N_){
	n = N_;
	s[0].init();
}

void Link(int u, int v){
	if(stage == 0){
		adj[u].push_back(v);
		adj[v].push_back(u);
		s[0].uni(u, v);

		if(adj[v].size() >= 3) swap(u, v);
		if(adj[u].size() >= 3){
			stage = 1;

			s[1].init(u);
			for(int i = 2; i <= 4; i ++)
				s[i].init(adj[u][i - 2]);

			for(int i = 1; i <= n; i ++)
				for(int j : adj[i]) if(j < i)
					for(int id = 1; id <= 4; id ++)
						s[id].uni(i, j);
		}
	}else{
		for(int id = 1; id <= 4; id ++)
			s[id].uni(u, v);
	}
}

int CountCritical(){
	int ans = 0;

	if(stage == 0){
		if(s[0].cyc.size() >= 2) ans = 0;
		else if(s[0].cyc.size() == 0) ans = n;
		else ans = s[0].sz[s[0].find(s[0].cyc.back())];
	}else{
		for(int id = 1; id <= 4; id ++)
			ans += (int)s[id].valid;
	}

	return ans;
}
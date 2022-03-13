#include <bits/stdc++.h>
using namespace std;

class stronglyConnected{
public:
	int n;
	vector<bool> vis;
	vector<int> st, sccID;
	vector<vector<int> > adj, radj, cc;

	stronglyConnected(int N) : n(N), vis(N, 0), sccID(N, -1), adj(N), radj(N) {}

	void addEdge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void dfs(int nw){
		vis[nw] = 1;
		for(int nx : adj[nw])
			if(!vis[nx]) dfs(nx);
		st.push_back(nw);
	}

	void dfs2(int nw, int cl, vector<int> &v){
		sccID[nw] = cl; v.push_back(nw);
		for(int nx : radj[nw])
			if(sccID[nx] == -1) dfs2(nx, cl, v);
	}

	void kosaraju(){
		for(int i = 0; i < n; i ++)
			if(!vis[i]) dfs(i);

		reverse(st.begin(), st.end());
		for(int i : st) if(sccID[i] == -1){
			cc.emplace_back();
			dfs2(i, (int)cc.size() - 1, cc.back());
		}
	}
};

class twoSat{
public:
	int n;
	vector<int> ans;
	stronglyConnected S;

	twoSat(int N) : n(N), ans(N, 0), S(2 * N) {}

	void clauseOr(int x, int y){
		x = max(2 * x, -1 - 2 * x);
		y = max(2 * y, -1 - 2 * y);
		S.addEdge(x ^ 1, y);
		S.addEdge(y ^ 1, x);
	}

	bool solve(){
		S.kosaraju();

		for(int i = 0; i < n; i ++)
			if(S.cc[2 * i] == S.cc[2 * i + 1])
				return false;

		for(int i = 0; i < n; i ++)
			ans[i] = S.cc[2 * i] > S.cc[2 * i + 1];
		return true;
	}
};
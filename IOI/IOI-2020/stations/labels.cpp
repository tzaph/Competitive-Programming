#include "labels.h"
#include <vector>
#include <functional>
using namespace std;

vector<int> label(int n, int k, vector<int> u, vector<int> v){
	vector<vector<int> > adj(n);
	for(int i = 0; i < n - 1; i ++){
		adj[u[i]].push_back(v[i]);
		adj[v[i]].push_back(u[i]);
	}

	vector<int> ans(n);
	int id = 0;

	function<void(int, int)> dfs = [&](int nw, int bf){
		if(bf == -1 || !ans[bf])
			ans[nw] = ++ id;

		for(int nx : adj[nw]) if(nx != bf)
			dfs(nx, nw);

		if(!ans[nw])
			ans[nw] = ++ id;
	};

	dfs(0, -1);
	return ans;
}
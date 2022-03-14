#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
const int MX = 200005;
const ll mod = 1000000000;

int n;
vector<pair<int, pair<int, int> > > node;
vector<int> adj[MX];
ll sm = 0, ans = 0;

ll wt(int id){
	return (node[id].second.second + mod - node[id].second.first + 1) % mod;
}

ll dfs(int nw, int bf){
	ll w = wt(nw);
	for(int nx : adj[nw]) if(nx != bf)
		(w += dfs(nx, nw)) %= mod;
	(ans += (w * ((sm + mod - w) % mod)) % mod) %= mod;
	return w;
}

void solve(vector<pair<int, int> > v){
	node.clear();
	for(int i = 0; i < MX; i ++) adj[i].clear();

	sort(v.begin(), v.end());

	for(int i = 0; i < n; i ++){
		int j = i + 1, ly = v[i].second;

		for(; j < n && v[i].first == v[j].first && ly + 1 == v[j].second; j ++, ly ++);
		j --;

		node.push_back({v[i].first, {v[i].second, v[j].second}});
		i = j;
	}

	for(int i = 0, j = 1; j < node.size(); j ++){
		for(; i < j && (node[i].first + 1 < node[j].first || (node[i].first + 1 == node[j].first && node[i].second.second < node[j].second.first)); i ++);

		for(; i < j && node[i].first + 1 == node[j].first && node[i].second.first <= node[j].second.second; i ++){
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
		i = max(i - 1, 0);
	}

	sm = 0;
	for(int i = 0; i < node.size(); i ++)
		(sm += wt(i)) %= mod;

	dfs(0, 0);
}

int DistanceSum(int N, int *X, int *Y){
	n = N;
	vector<pair<int, int> > v;
	for(int i = 0; i < n; i ++)
		v.push_back({X[i], Y[i]});

	solve(v);
	for(int i = 0; i < n; i ++)
		swap(v[i].first, v[i].second);
	solve(v);

	return ans;
}
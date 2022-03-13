// Heavy Light Decomposition + Euler tour
// Graph is a tree and 0 indexed, weighted on vertex or edge
// Update vertex and query sum in path/subtree
// Idea to divide the tree to logn disjoint paths
// Queries work in log^2 at worst

// A path u to head[u]: [in[head[u]], u]
// Subtree rooted at u: [in[u], in[u] + sz[u])

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
const int MX = 200005;
const ll inf_ll = 8e18 + 69;

int n, m, q, par[MX], depth[MX], sz[MX], wt[MX];
vector<int> adj[MX];
int head[MX];
int in[MX], rev[MX], tim = 0;
int weighted_edge = 0; // if edge is weighted, =1

void dfs_sz(int nw){
	sz[nw] = 1;
	for(int &nx : adj[nw]){
		par[nx] = nw;
		depth[nx] = depth[nw] + 1;
		adj[nx].erase(find(adj[nx].begin(), adj[nx].end(), nw));
		dfs_sz(nx);
		sz[nw] += sz[nx];
		if(sz[nx] > sz[adj[nw][0]])
			swap(nx, adj[nw][0]);
	}
}

void dfs_hld(int nw){
	in[nw] = tim ++;
	rev[in[nw]] = nw;
	for(int nx : adj[nw]){
		head[nx] = (nx == adj[nw][0] ? head[nw] : nx);
		dfs_hld(nx);
	}
}

void init(int root = 0){
	par[root] = depth[root] = tim = 0;
	dfs_sz(root);
	head[root] = root;
	dfs_hld(root);
}

// normal lazy segtree range sum
ll lz[MX * 4];
pair<ll, int> st[MX * 4];

void prop(int nd, int cl, int cr){
	if(lz[nd]){
		st[nd].first += lz[nd];
		if(cl != cr){
			lz[nd * 2] += lz[nd];
			lz[nd * 2 + 1] += lz[nd];
		}
		lz[nd] = 0;
	}
}

void build_tree(int nd, int cl, int cr){
	lz[nd] = 0;
	if(cl == cr){
		st[nd] = {0, rev[cl]};
		return;
	}

	build_tree(nd * 2, cl, (cl + cr) / 2);
	build_tree(nd * 2 + 1, (cl + cr) / 2 + 1, cr);
	st[nd] = min(st[nd * 2], st[nd * 2 + 1]);
}

void upd_tree(int nd, int cl, int cr, int lf, int rg, ll val){
	prop(nd, cl, cr);
	if(lf > rg || rg < cl || cr < lf) return;
	if(lf <= cl && cr <= rg){
		lz[nd] += val;
		prop(nd, cl, cr);
		return;
	}

	upd_tree(nd * 2, cl, (cl + cr) / 2, lf, rg, val);
	upd_tree(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg, val);
	st[nd] = min(st[nd * 2], st[nd * 2 + 1]);
}

pair<ll, int> que_tree(int nd, int cl, int cr, int lf, int rg){
	prop(nd, cl, cr);
	if(lf > rg || rg < cl || cr < lf) return {inf_ll, 0};
	if(lf <= cl && cr <= rg) return st[nd];

	return min( // merge function, change accordingly
		que_tree(nd * 2, cl, (cl + cr) / 2, lf, rg),
		que_tree(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg)
	);
}

void print_tree(int nd, int cl, int cr){
	cout << nd << " " << cl << " " << cr << ": (" << st[nd].first << ", " << st[nd].second << ")\n";
	if(cl == cr) return;
	print_tree(nd * 2, cl, (cl + cr) / 2);
	print_tree(nd * 2 + 1, (cl + cr) / 2 + 1, cr);
}

void modify_path(int u, int v, ll w){
	for(; head[u] != head[v]; v = par[head[v]]){
		if(depth[head[u]] > depth[head[v]])
			swap(u, v);
		upd_tree(1, 0, n - 1, in[head[v]], in[v], w);
	}
	if(depth[u] > depth[v]) swap(u, v);
	upd_tree(1, 0, n - 1, in[u] + weighted_edge, in[v], w);
}

// minimum weight edge in path u to v, change accordingly
pair<ll, int> query_path(int u, int v){
	pair<ll, int> res = {inf_ll, 0};
	for(; head[u] != head[v]; v = par[head[v]]){
		if(depth[head[u]] > depth[head[v]])
			swap(u, v);
		res = min(res, que_tree(1, 0, n - 1, in[head[v]], in[v])); // merge
	}
	if(depth[u] > depth[v]) swap(u, v);
	res = min(res, que_tree(1, 0, n - 1, in[u] + weighted_edge, in[v])); // merge
	return res;
}

void modify_subtree(int u, ll w){ // in[u] + sz[u] = out[u]
	upd_tree(1, 0, n - 1, in[u] + weighted_edge, in[u] + sz[u] - 1, w);
}
#include "split.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> ans, disc, low, sz, par;
vector<int> adj[100005], adj_st[100005];
pair<int, int> a[3];
int n, m, A, B, C, timer = 0;

void init(){
	a[0] = {A, 1}; a[1] = {B, 2}; a[2] = {C, 3};
	sort(a, a + 3);
	disc.assign(n, 0); low.assign(n, 0);
	sz.resize(n); par.resize(n, -1);
	ans.assign(n, a[2].second);
}

void dfs(int nw){
	sz[nw] = 1;
	disc[nw] = low[nw] = ++timer;
	for(int nx : adj[nw]){
		if(nx != par[nw]){
			if(!low[nx]){
				par[nx] = nw; dfs(nx);
				sz[nw] += sz[nx];
				low[nw] = min(low[nw], low[nx]);
				adj_st[nw].push_back(nx);
			}else{
				low[nw] = min(low[nw], disc[nx]);
			}
		}
	}
	return;
}

int cnt, col;
void fill_ans(int nw, int tp){
	cnt --; ans[nw] = col;
	if(!tp){
		for(int nx : adj_st[nw])
			if(cnt) fill_ans(nx, tp);
	}else{
		for(int nx : adj[nw])
			if(cnt && ans[nx] == a[2].second) fill_ans(nx, tp);
	}
}

vector<int> find_split(int N, int _A, int _B, int _C, vector<int> P, vector<int> Q){
	n = N; m = P.size();
	A = _A, B = _B, C = _C;
	init();

	for(int i = 0; i < m; i ++){
		adj[P[i]].push_back(Q[i]);
		adj[Q[i]].push_back(P[i]);
	}
	par[0] = -1;
	dfs(0);

	int rt = 0;
	for(;;){
		bool found = true;
		for(int nx : adj_st[rt]){
			if(sz[nx] >= a[0].first){
				found = false;
				rt = nx; break;
			}
		}
		if(found) break;
	}

	if(sz[rt] + a[1].first <= n){
		cnt = a[0].first, col = a[0].second;
		fill_ans(rt, 0);
		
		cnt = a[1].first, col = a[1].second;
		fill_ans(par[rt], 1);
	}else{
		cnt = a[1].first, col = a[1].second;
		ans[rt] = col; cnt --;
		for(int nx : adj_st[rt]) 
			if(cnt && low[nx] < disc[rt]) //prioritize
				fill_ans(nx, 0);
		for(int nx : adj_st[rt])
			if(cnt && low[nx] >= disc[rt])
				fill_ans(nx, 0);

		cnt = a[0].first, col = a[0].second;
		if(par[rt] != -1) fill_ans(par[rt], 1);
		if(cnt) ans = vector<int> (n, 0);
	}

	return ans;
}
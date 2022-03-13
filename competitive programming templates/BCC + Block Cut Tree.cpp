#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5 + 5;

/* Code for biconnected and block cut tree for undirected graph */
// note: MX = maximum number of vertices, *2 is necessary
int n, m, tin[MX], low[MX], tim = 0;
vector<int> adj[MX], bcc[MX * 2], st;
vector<vector<int> > components;
bitset<MX> is_articulation;
int bcc_id[MX], val[MX * 2];
int wt[MX]; // vertex weight

void dfs(int nw, int bf = 0){
	int child = 0;
	tin[nw] = low[nw] = ++tim;
	st.push_back(nw);

	for(int nx : adj[nw]) if(nx != bf){
		if(tin[nx])
			low[nw] = min(low[nw], tin[nx]);
		else{
			child ++;
			dfs(nx, nw);
			low[nw] = min(low[nw], low[nx]);

			if((bf != 0 && low[nx] >= tin[nw]) || (bf == 0 && child > 1)){
				is_articulation[nw] = 1;
				vector<int> gt;
				gt.push_back(nw);
				for(; gt.size() != nx;){
					gt.push_back(st.back());
					st.pop_back();
				}
				components.push_back(gt);
			}
		}
	}

	if(bf == 0 && !st.empty()){
		components.push_back(st);
		st.clear();
	}
}

void initBCT(){
	dfs(1);

	int id = 0;
	for(int i = 1; i <= n; i ++)
		if(is_articulation[i]){
			bcc_id[i] = ++ id;
			val[bcc_id[i]] = wt[i];
		}

	for(auto i : components){
		id ++;
		for(auto j : i){
			val[id] = max(val[id], wt[j]);
			if(is_articulation[j]){
				bcc[bcc_id[j]].push_back(id);
				bcc[id].push_back(bcc_id[j]);
			}else{
				bcc_id[j] = id;
			}
		}
	}
}
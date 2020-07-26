#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, m, tin[200005], low[200005];
vector<int> adj[200005], adj_bcc[200005];
vector<int> euler_tour;
int bcc_id = 0, tim = 1, cnt = 0;
ll sz[200005], ans;

void dfs(int nw, int bf){
	tin[nw] = low[nw] = tim ++;
	euler_tour.push_back(nw);
	cnt ++;

	for(int nx : adj[nw]) if(nx != bf){
		if(!tin[nx]){
			dfs(nx, nw);
			low[nw] = min(low[nw], low[nx]);
			if(low[nx] >= tin[nw]){
				adj_bcc[nw].push_back(bcc_id + n);
				while(adj_bcc[bcc_id + n].empty() || adj_bcc[bcc_id + n].back() != nx){
					adj_bcc[bcc_id + n].push_back(euler_tour.back());
					euler_tour.pop_back();
				}
				bcc_id ++;
			}
		}else
			low[nw] = min(low[nw], tin[nx]);
	}
}

void exc(int nw){
	if(nw < n) sz[nw] = 1;
	for(int nx : adj_bcc[nw]){
		exc(nx);
		sz[nw] += sz[nx];
		if(nw >= n)
			ans -= sz[nx] * 1ll * (sz[nx] - 1) * 1ll * (ll)adj_bcc[nw].size();
	}

	if(nw >= n)
		ans -= (cnt - sz[nw]) * 1ll * (cnt - sz[nw] - 1) * 1ll * (ll)adj_bcc[nw].size();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for(int u, v, i = 0; i < m; i ++){
		cin >> u >> v;
		u --; v --;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 0; i < n; i ++) if(!tin[i]){
		cnt = 0;
		dfs(i, -1);
		ans += cnt * 1ll * (cnt - 1) * 1ll * (cnt - 2);
		exc(i);
	}

	cout << ans << endl;
}
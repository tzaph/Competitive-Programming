#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MX = 505;
const ll infll = 4e18 + 6969;

struct MCMF{
	struct edge{
		int v;
		ll cap, cost;
		int rev;
	};

	ll flow, cost;
	int st, ed, n;
	ll dist[MX], H[MX];
	int pv[MX], pe[MX];
	vector<edge> adj[MX];

	bool dijk(){
		priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
		fill(dist, dist + n + 1, infll);
		dist[st] = 0; pq.push({0, st});
		for(; pq.size();){
			ll cstnw = pq.top().first;
			int nw = pq.top().second;
			pq.pop();
			if(dist[nw] < cstnw) continue;
			for(int i = 0; i < adj[nw].size(); i ++){
				auto e = adj[nw][i];
				int nx = e.v;
				pair<ll, int> y = {dist[nw] + e.cost + H[nw] - H[nx], nx};
				if(e.cap > 0 && dist[nx] > y.first){
					dist[nx] = y.first;
					pe[nx] = i; pv[nx] = nw;
					pq.push(y);
				}
			}
		}

		if(dist[ed] == infll) return false;
		for(int i = 0; i <= n; i ++)
			H[i] += dist[i];

		ll f = infll;
		for(int i = ed; i != st; i = pv[i])
			f = min(f, adj[pv[i]][pe[i]].cap);

		flow += f;
		cost += f * H[ed];

		for(int i = ed; i != st; i = pv[i]){
			auto &e = adj[pv[i]][pe[i]];
			e.cap -= f;
			adj[i][e.rev].cap += f;
		}

		return true;
	}

	void solve(int st, int ed){
		this -> st = st;
		this -> ed = ed;
		flow = cost = 0;
		fill(H, H + n + 1, 0);
		while(dijk());
	}

	void init(int n){
		this -> n = n;
		for(int i = 0; i <= n; i ++)
			adj[i].clear();
	}

	void addEdge(int u, int v, ll cap, ll cost){
		adj[u].push_back({v, cap, cost, (int)adj[v].size()});
		adj[v].push_back({u, 0, -cost, (int)adj[u].size() - 1});
	}
} mf;
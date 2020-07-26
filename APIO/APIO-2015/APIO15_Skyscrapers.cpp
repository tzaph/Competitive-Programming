#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> >adj[30005];
set<int> building[30005];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
int n, m, st, ed, dist[30005];
int ans=1e9+69;
int main(){
	scanf("%d%d", &n, &m);
	int b, p;
	scanf("%d%d", &st, &p); building[st].insert(p);
	scanf("%d%d", &ed, &p); building[ed].insert(p);
	for(int i=2; i<m; i++){
		scanf("%d%d", &b, &p);
		building[b].insert(p);
	}
	for(int i=0; i<n; i++) for(int p:building[i]){
		for(int j=1; i+j*p<n; j++){
			adj[i].push_back({i+j*p, j});
			if(building[i+j*p].count(p)) break;
		}
		for(int j=1; i-j*p>=0; j++){
			adj[i].push_back({i-j*p, j});
			if(building[i-j*p].count(p)) break;
		}
	}
	for(int i=0; i<n; i++) dist[i]=1e9+69;
	pq.push({0, st}); dist[st]=0;
	for(;!pq.empty();){
		int dst=pq.top().first, nw=pq.top().second;
		pq.pop();
		if(dist[nw]!=dst) continue;
		if(nw==ed) ans=min(ans, dst);
		for(pair<int, int> nx:adj[nw]){
			if(dist[nx.first]>dist[nw]+nx.second){
				dist[nx.first]=dist[nw]+nx.second;
				pq.push({dist[nx.first], nx.first});
			}
		}
	}
	if(ans==1e9+69) ans=-1;
	printf("%d\n", ans);
}
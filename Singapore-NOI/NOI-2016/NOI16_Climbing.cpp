#include<bits/stdc++.h>
using namespace std;
bool vis[1005], appl[505][505];
vector<int>adj[1005];
int match[1005];
bool matching(int nw){
	if(vis[nw]) return false;
	vis[nw]=true;
	for(int nx:adj[nw]){
		if(match[nx]==-1 || matching(match[nx])){
			match[nw]=nx; match[nx]=nw;
			return true;
		}
	}
	return false;
}
vector<pair<pair<int, int>, int> >v;
int n, dist[505][505];
int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int x, y, s; scanf("%d%d%d", &x, &y, &s);
		v.push_back({{x,y},s});
	}
	for(int i=0; i<n; i++) for(int j=0; j<n; j++)
		dist[i][j]=100000000;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			int dst=max(abs(v[i].first.first-v[j].first.first), abs(v[i].first.second-v[j].first.second));
			if(dst<=max(v[i].second, v[j].second)){
				if(v[i].first.second<v[j].first.second)
					dist[i][j]=0;
				else if(v[i].first.second>v[j].first.second)
					dist[j][i]=0;
			}
		}
	}
	for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<n; k++)
		if(dist[j][i]+dist[i][k]<dist[j][k])
			dist[j][k]=dist[j][i]+dist[i][k];
	for(int i=0; i<n; i++) for(int j=i+1; j<n; j++)
		if(dist[i][j]==0)
			adj[i].push_back(j+n);
		else if(dist[j][i]==0)
			adj[j].push_back(i+n);
	int mvc=0;
	memset(match, -1, sizeof(match));
	for(int i=0; i<n; i++){
		if(match[i]!=-1) continue;
		memset(vis, false, sizeof(vis));
		if(matching(i)) mvc++;
	}
	if(mvc==0) mvc=n+2;
	printf("%d\n", n-mvc+1);
	return 0;
}
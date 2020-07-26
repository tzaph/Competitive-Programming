#include"dreaming.h"
#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> >adj[100005];
vector<int>v;
bool vis[100005];
int par[100005], X[100005];
pair<int, int> dfs(int nw, int bf){
	pair<int, int> rs={0, nw};
	for(pair<int, int> i:adj[nw]){
		if(i.second==bf) continue;
		pair<int, int> rst=dfs(i.second, nw);
		rs=max(rs, {rst.first+i.first, rst.second});
	}
	X[nw]=rs.first;
	par[nw]=bf; vis[nw]=true;
	return rs;
}
int travelTime(int n, int m, int L, int A[], int B[], int T[]){
	for(int i=0; i<m; i++){
		adj[A[i]].push_back({T[i], B[i]});
		adj[B[i]].push_back({T[i], A[i]});
	}
	int ans, diameter=0;
	for(int i=0; i<n; i++){
		if(vis[i]) continue;
		pair<int, int> rs=dfs(dfs(i, i).second, -1);
		int nd=rs.second, mn=rs.first;
		for(; nd>=0; nd=par[nd]) mn=min(mn, max(X[nd], rs.first-X[nd]));
		v.push_back(mn); diameter=max(diameter, rs.first);
	}
	sort(v.begin(), v.end()); reverse(v.begin(), v.end());
	if(v.size()>2){
		ans=L+v[0]+v[1];
		for(int i=2; i<v.size(); i++)
			ans=max(ans, 2*L+v[1]+v[i]);
	}else if(v.size()==2) ans=L+v[0]+v[1];
	else ans=0;
	ans=max(ans, diameter);
	return ans;
}
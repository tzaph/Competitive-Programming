#include "game.h"
#include<bits/stdc++.h>
using namespace std;
 
int par[1569], sz[1569];
int m, cnt[1569][1569];
int find(int x){
	return par[x]==x?x:par[x]=find(par[x]);
}
void uni(int a, int b){
	if(a<b) swap(a, b);
	par[a]=b; sz[b]+=sz[a];
}
 
void initialize(int n){
	m=n; memset(cnt, 0, sizeof(cnt));
	for(int i=0; i<n; i++){
		par[i]=i; sz[i]=1;
	}
}
 
int hasEdge(int u, int v){
	u=find(u); v=find(v);
	cnt[u][v]++; cnt[v][u]++;
	if(cnt[u][v]==sz[u]*sz[v]){
		uni(u, v);
		for(int i=0; i<m; i++){
			cnt[min(u, v)][i]+=cnt[max(u, v)][i];
			cnt[i][min(u, v)]+=cnt[i][max(u, v)];
		}
		return 1;
	}
	return 0;
}
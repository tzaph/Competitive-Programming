#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mxn=1e6+5;
int n, q, par[mxn], sz[mxn];
pair<int, int>h[mxn];
bool vis[mxn];
int f(int a){return par[a]=(par[a]==a)?a:f(par[a]);}
ll calc(int x){return (ll)sz[f(x)]*(sz[f(x)]+1)/2;}
int main(){
	scanf("%d%d", &n, &q);
	for(int i=0; i<n; i++){
		scanf("%d", &h[i].first);
		h[i].second=i; par[i]=i;
		vis[i]=false; sz[i]=1;
	}
	vector<ll>val;
	vector<int>id;
	id.push_back(0); val.push_back(0ll);
	sort(h, h+n);
	ll v=0ll, vt=0ll; int tmp=h[0].first;
	for(int i=0; i<n; i++){
		if(h[i].second>0 && vis[h[i].second-1]){
			int uu=h[i].second, vv=h[i].second-1;
			v-=calc(vv);
			uu=f(uu); vv=f(vv);
			sz[uu]+=sz[vv]; par[vv]=uu;
		}
		if(h[i].second<n-1 && vis[h[i].second+1]){
			int uu=h[i].second, vv=h[i].second+1;
			v-=calc(vv);
			uu=f(uu); vv=f(vv);
			sz[uu]+=sz[vv]; par[vv]=uu;
		}
		v+=calc(h[i].second);
		if(tmp!=h[i].first){
			id.push_back(tmp);
			val.push_back(vt);
			tmp=h[i].first;
		}
		vt=v; vis[h[i].second]=true;
	}
	id.push_back(tmp);
	val.push_back(vt);
	for(int i=0, h; i<q; i++){
		scanf("%d", &h);
		int ii=lower_bound(id.begin(), id.end(), h)-id.begin();
		if(id[ii]!=h) ii--;
		printf("%lld\n", val[ii]);
	}
	return 0;
}
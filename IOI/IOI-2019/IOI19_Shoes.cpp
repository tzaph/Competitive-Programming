#include "shoes.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mxn=200069;
ll fw[mxn];
void add(ll x, ll val){
	for(ll i=x; i<mxn; i+=i&-i) fw[i]+=val;
}
ll que(ll x){
	ll r=0ll;
	for(ll i=x; i>0; i-=i&-i) r+=fw[i];
	return r;
}
ll count_swaps(vector<int>S){
	ll n=S.size()/2, res=0;
	vector<pair<ll, ll> >swp, grp[mxn];
	for(ll i=0; i<2*n; i++) grp[abs(S[i])].push_back({S[i], i});
	for(int i=1; i<=n; i++){
		sort(grp[i].begin(), grp[i].end());
		int num=grp[i].size()/2;
		for(int j=0; j<num; j++){
			int l=grp[i][j].second, r=grp[i][j+num].second;
			if(l>r){swap(l, r); res++;}
			swp.push_back({l+1, r+1});
		}
	}
	sort(swp.begin(), swp.end());
	for(int i=1; i<=2*n; i++) add(i, 1);
	for(int i=0; i<swp.size(); i++){
		res+=que(swp[i].second-1)-que(swp[i].first);
		add(swp[i].first, -1); add(swp[i].second, -1);
	}
	return res;
}
#include"robots.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n, a, b;
vector<pair<ll, ll> >v;
vector<ll>vv[50005];
bool ok(ll x){
	ll sisa=0;
	vector<ll>isi;
	priority_queue<ll>pq;
	for(ll i=0; i<vv[0].size(); i++)
		isi.push_back(vv[0][i]);
	for(ll i=1; i<=a; i++){
	//	cout<<sisa<<"->";
		for(ll j=0; j<(ll)vv[i].size(); j++)
			pq.push(vv[i][j]);
		ll siz=vv[i].size();
		if(sisa>=siz-x) sisa-=siz-x;
		else{
			for(ll j=1; j<=siz-x-sisa; j++){
				if(pq.empty()) return false;
				isi.push_back(pq.top()); pq.pop();
			}
			sisa=0;
		}
	//	cout<<sisa<<endl;
	}
	sort(isi.begin(), isi.end());
	for(ll i=0; i<(ll)isi.size(); i++){
		ll tmp=i/x+1;
		if(tmp>b || tmp>isi[i]) return false;
	}
	return true;
}
int putaway(int _a, int _b, int _t, int x[], int y[], int w[], int s[]){
	n=_t;
	a=_a; b=_b;
	sort(x, x+a); sort(y, y+b);
	v.resize(n);
	for(ll i=0; i<n; i++)
		v[i]={w[i], s[i]};
	for(ll i=0; i<n; i++){
		ll l=0, r=a-1, md;
		ll wt=0, sz=0;
		while(l<=r){
			md=(l+r)/2;
			if(v[i].first<x[md]){
				wt=a-md;
				r=md-1;
			}else l=md+1;
		}
		l=0, r=b-1;
		while(l<=r){
			md=(l+r)/2;
			if(v[i].second<y[md]){
				sz=b-md;
				r=md-1;
			}else l=md+1;
		}
		vv[wt].push_back(sz);
	}
	ll ans=-1;
	ll l=1, r=n, md;
	while(l<=r){
		md=(l+r)/2;
		if(ok(md)){
			ans=md; r=md-1;
		}else l=md+1;
	}
	return ans;
}
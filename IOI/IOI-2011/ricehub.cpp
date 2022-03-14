#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll cnt[100005];
bool check(int n, int pos, ll lim){
	int l, r, md;
	ll rs;
	for(int i=1; i<=n-pos+1; i++){
		l=i; r=i+pos-1;
		md=(l+r)>>1;
		rs=(cnt[r]-cnt[md])-(cnt[md-pos%2]-cnt[l-1]);
		if(rs<=lim) return true;
	}
	return false;
}
int besthub(int R, int L, int* X, ll B){
	for(int i=1; i<=R; i++)
		cnt[i]=cnt[i-1]+X[i-1];
	int l=0, r=R;
	while(l!=r){
		int md=(l+r+1)>>1;
		if(check(R, md, B)) l=md;
		else r=md-1;
	}
	return l;
}
#include "holiday.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=4e18;
ll ans=0ll;
pair<int, int>a[100005];
int n, s, d, ptr, pos[100005];
pair<ll, int>st[100005*4];
void upd(int nd, int cl, int cr, int pos, bool is){
	if(cl == cr){
		if(is) st[nd] = {a[pos].first, 1};
		else st[nd] = {0, 0};
		return;
	}
	int md = (cl+cr)/2;
	if(pos<=md) upd(nd*2, cl, md, pos, is);
	else upd(nd*2+1, md+1, cr, pos, is);
	st[nd] = {st[nd*2].first+st[nd*2+1].first, st[nd*2].second+st[nd*2+1].second};
}
ll k_best(int nd, int cl, int cr, int k){
	if(k <= 0) return 0;
	if(st[nd].second <= k) return st[nd].first;
	int md = (cl+cr)/2;
	if(st[nd*2].second >= k)
		return k_best(nd*2, cl, md, k);
	return st[nd*2].first + k_best(nd*2+1, md+1, cr, k-st[nd*2].second);
}
void solve(int l, int r, int opt_l, int opt_r){
	if(l > r) return;
	int md = (l+r)/2;
	pair<ll, int> res = {-inf, -1};
	if(md < ptr)
		for(int i=md; i<ptr; i++)
			upd(1, 1, n, pos[i], true);
	else
		for(int i=ptr; i<md; i++)
			upd(1, 1, n, pos[i], false);
	ptr = md;
	for(int i=opt_l; i<=opt_r; i++){
		upd(1, 1, n, pos[i], true);
		res = max(res, {k_best(1, 1, n, d+2*md-s-i), -i});
	}
	ans = max(ans, res.first);
	int opt = -res.second;
	for(int i=opt; i<=opt_r; i++)
		upd(1, 1, n, pos[i], false);
	solve(md+1, r, opt, opt_r);
	for(int i=opt_l; i<opt; i++)
		upd(1, 1, n, pos[i], false);
	solve(l, md-1, opt_l, opt);
}
ll findMaxAttraction(int N, int S, int D, int A[]){
	n = N, s = S+1, d = D;
	for(int i=1; i<=n; i++)
		a[i] = {A[i-1], i};
	sort(a+1, a+n+1, greater<pair<int, int> >());
	for(int i=1; i<=n; i++)
		pos[a[i].second] = i;
	ptr = s+1;
	solve(1, s, s, n);
	for(int i=1; i<=n; i++){
		pos[n-a[i].second+1] = i;
		upd(1, 1, n, i, false);
	}
	s = n-s+1;
	ptr = s+1;
	solve(1, s, s, n);
	return ans;
}
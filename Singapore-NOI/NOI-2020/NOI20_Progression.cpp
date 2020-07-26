/*
	* NOI 2020 C Progression
	* Take the difference array
	* Problem becomes finding longest subarray such that all elements are equal
	* We can maintain the prefix, suffix, and middle of the segment
	* Two adjacent segments where the left segment suffix is the same as the right segment prefix
	* Can become a candidate answer
	* Updates and queries can be done with lazy propagation segment tree
*/
#include <stdio.h>
#include <assert.h>
#include <algorithm>
using namespace std;

#define ll long long

int n, q;
ll arr[300005], diff[300005];

struct node{
	int pref_len, suff_len, sub_len;
	ll pref_val, suff_val, sub_val;
	int len; ll sum;

	node(){}
	node(ll val):sum(val){
		len = 1;
		pref_val = val; pref_len = 1;
		suff_val = val; suff_len = 1;
		sub_val = 0; sub_len = 0;
	}

	void add(ll val){
		pref_val += val;
		suff_val += val;
		sub_val += val;
		sum += val * 1ll * len;
	}
	void set(ll val){
		pref_val = suff_val = sub_val = val;
		pref_len = suff_len = len;
		sub_len = max(0, len - 2);
		sum = val * 1ll * len;
	}
} st[300005 * 4];

ll laz_set[300005 * 4], laz_add[300005 * 4];
bool lset[300005 * 4];

#define md (cl + cr) / 2
#define lc cl, md
#define rc md + 1, cr

node merge(node lf, node rg){
	node res;
	res.len = lf.len + rg.len;
	res.sum = lf.sum + rg.sum;

	res.pref_val = lf.pref_val;
	res.pref_len = lf.pref_len;
	if(lf.pref_len == lf.len && lf.pref_val == rg.pref_val)
		res.pref_len = lf.len + rg.pref_len;

	res.suff_val = rg.suff_val;
	res.suff_len = rg.suff_len;
	if(rg.suff_len == rg.len && lf.suff_val == rg.suff_val)
		res.suff_len = lf.suff_len + rg.len;

	res.sub_val = lf.sub_val;
	res.sub_len = lf.sub_len;
	if(res.sub_len < rg.sub_len){
		res.sub_val = rg.sub_val;
		res.sub_len = rg.sub_len;
	}

	if(min(lf.len - 1, lf.suff_len) > res.sub_len){
		res.sub_len = min(lf.len - 1, lf.suff_len);
		res.sub_val = lf.suff_val;
	}
	if(min(rg.len - 1, rg.pref_len) > res.sub_len){
		res.sub_len = min(rg.len - 1, rg.pref_len);
		res.sub_val = rg.pref_val;
	}
	if(lf.suff_val == rg.pref_val && min(lf.len - 1, lf.suff_len) + min(rg.len - 1, rg.pref_len) > res.sub_len){
		res.sub_len = min(lf.len - 1, lf.suff_len) + min(rg.len - 1, rg.pref_len);
		res.sub_val = lf.suff_val;
	}

	return res;
}

void radd(int nd, ll v){
	if(lset[nd])
		st[nd].set(laz_set[nd] += v);
	else{
		laz_add[nd] += v;
		st[nd].add(v);
	}
}
void rset(int nd, ll v){
	lset[nd] = true;
	laz_add[nd] = 0;
	st[nd].set(laz_set[nd] = v);
}

void push(int nd, int cl, int cr){
	if(lset[nd]){
		if(cl != cr){
			rset(nd * 2, laz_set[nd]);
			rset(nd * 2 + 1, laz_set[nd]);
		}
		lset[nd] = false;
		laz_set[nd] = 0ll;
	}

	if(laz_add[nd]){
		if(cl != cr){
			radd(nd * 2, laz_add[nd]);
			radd(nd * 2 + 1, laz_add[nd]);
		}
		laz_add[nd] = 0ll;
	}
}

void build(int nd, int cl, int cr){
	lset[nd] = false;
	laz_add[nd] = laz_set[nd] = 0ll;

	if(cl == cr){
		st[nd] = node(diff[cl]);
		return;
	}

	build(nd * 2, lc);
	build(nd * 2 + 1, rc);
	st[nd] = merge(st[nd * 2], st[nd * 2 + 1]);
}

node que(int nd, int cl, int cr, int l, int r){
	if(l <= cl && cr <= r) return st[nd];
	push(nd, cl, cr);

	if(r <= md) return que(nd * 2, lc, l, r);
	if(md < l) return que(nd * 2 + 1, rc, l, r);
	return merge(que(nd * 2, lc, l, r), que(nd * 2 + 1, rc, l, r));
}

void add(int nd, int cl, int cr, int l, int r, ll v){
	if(l <= cl && cr <= r) return radd(nd, v);
	push(nd, cl, cr);

	if(r <= md) add(nd * 2, lc, l, r, v);
	else if(md < l) add(nd * 2 + 1, rc, l, r, v);
	else{
		add(nd * 2, lc, l, md, v);
		add(nd * 2 + 1, rc, md + 1, r, v);
	}

	st[nd] = merge(st[nd * 2], st[nd * 2 + 1]);
}

void set(int nd, int cl, int cr, int l, int r, ll v){
	if(l <= cl && cr <= r) return rset(nd, v);
	push(nd, cl, cr);

	if(r <= md) set(nd * 2, lc, l, r, v);
	else if(md < l) set(nd * 2 + 1, rc, l, r, v);
	else{
		set(nd * 2, lc, l, md, v);
		set(nd * 2 + 1, rc, md + 1, r, v);
	}

	st[nd] = merge(st[nd * 2], st[nd * 2 + 1]);
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i ++){
		scanf("%lld", &arr[i]);
		diff[i] = arr[i] - arr[i - 1];
	}

	build(1, 1, n);

	for(int tp, l, r; q --;){
		scanf("%d%d%d", &tp, &l, &r);
		
		if(tp == 1){
			ll s, c;
			scanf("%lld %lld", &s, &c);

			add(1, 1, n, l, l, s);
			if(l != r) add(1, 1, n, l + 1, r, c);
			if(r != n) add(1, 1, n, r + 1, r + 1, -(s + (r - l) * 1ll * c));
		}
		else if(tp == 2){
			ll s, c;
			scanf("%lld %lld", &s, &c);

			ll old_sum = que(1, 1, n, l, r).sum;
			ll pref;
			if(l == 1) pref = 0ll;
			else pref = que(1, 1, n, 1, l - 1).sum;

			set(1, 1, n, l, l, s - pref);
			if(l != r) set(1, 1, n, l + 1, r, c);
			if(r != n){
				ll new_sum = (s - pref) + (r - l) * 1ll * c;
				add(1, 1, n, r + 1, r + 1, old_sum - new_sum);
			}
		}
		else if(tp == 3){
			node res = que(1, 1, n, l, r);
			int len = max(res.pref_len, res.suff_len + 1);
			len = max(len, res.sub_len + 1);
			len = min(len, res.len);

			printf("%d\n", len);
		}
	}

	return 0;
}

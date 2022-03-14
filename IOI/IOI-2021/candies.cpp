#include "candies.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MX = 200005;

struct segtree{
	int n;
	ll suffmn[MX * 2], suffmx[MX * 2], sm[MX * 2], vals[MX];

	segtree(int x) : n(x){
		memset(suffmn, 0, sizeof(suffmn));
		memset(suffmx, 0, sizeof(suffmx));
		memset(sm, 0, sizeof(sm));
		memset(vals, 0, sizeof(vals));
	}

	#define md (cl + cr) / 2
	#define lc nd + 1
	#define rc nd + 2 * (md - cl + 1)

	void update(int nd, int cl, int cr, int ps, ll val){
		if(ps < cl || cr < ps) return;
		if(cl == cr){
			suffmn[nd] = suffmx[nd] = sm[nd] = val;
			return;
		}

		update(lc, cl, md, ps, val);
		update(rc, md + 1, cr, ps, val);

		suffmn[nd] = min(suffmn[lc] + sm[rc], suffmn[rc]);
		suffmx[nd] = max(suffmx[lc] + sm[rc], suffmx[rc]);
		sm[nd] = sm[lc] + sm[rc];
	}

	void upd(int ps, ll val){
		vals[ps] = val;
		update(1, 0, n - 1, ps, val);
	}

	// smallest suff s.t. mx - mn > c
	pair<pair<ll, ll>, ll> query(int nd, int cl, int cr, ll sfmn, ll sfmx, ll sfsm, int c){
		if(cl == cr)
			return {{min(sfmn, sfsm + suffmn[nd]), max(sfmx, sfsm + suffmx[nd])}, cl};

		ll nwsfmn = min(sfmn, sfsm + suffmn[rc]);
		ll nwsfmx = max(sfmx, sfsm + suffmx[rc]);
		ll nwsfsm = sfsm + sm[rc];

		if(nwsfmx - nwsfmn > c)
			return query(rc, md + 1, cr, sfmn, sfmx, sfsm, c);
		return query(lc, cl, md, nwsfmn, nwsfmx, nwsfsm, c);
	}

	pair<pair<ll, ll>, ll> que(int c){
		return query(1, 0, n - 1, 0, 0, 0, c);
	}

	int tp(int x){
		return vals[x];
	}
};

vector<pair<int, int> > queriesL[MX], queriesR[MX];

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v){
	int n = c.size(), q = v.size();
	vector<int> ans(n);
	segtree st(q);

	for(int i = 0; i < q; i ++){
		queriesL[l[i]].push_back({i, v[i]});
		queriesR[r[i]].push_back({i, v[i]});
	}

	for(int i = 0; i < n; i ++){
		for(pair<int, int> j : queriesL[i])
			st.upd(j.first, -j.second);

		auto gt = st.que(c[i]);
		ll mn = gt.first.first, mx = gt.first.second, id = gt.second;
		if(mx - mn <= c[i] || st.tp(id) >= 0) ans[i] = -mn;
		else ans[i] = c[i] - mx;

		for(pair<int, int> j : queriesR[i])
			st.upd(j.first, 0);
	}

	return ans;
}
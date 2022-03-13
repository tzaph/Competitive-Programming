#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MX = 300005;
const int inf = 1e9 + 69;

struct node{
	int mx, mxs, mxc;
	int mn, mns, mnc;
	int lz;
	ll sum;

	node(int val = 0){
		mn = mx = sum = val;
		mxc = mnc = 1;
		mxs = -inf; mns = inf;
		lz = 0; 
	}
};

node merge(node a, node b){
	node rs;
	rs.sum = a.sum + b.sum;

	rs.mx = max(a.mx, b.mx);
	if(a.mx == b.mx){
		rs.mxc = a.mxc + b.mxc;
		rs.mxs = max(a.mxs, b.mxs);
	}else if(a.mx > b.mx){
		rs.mxc = a.mxc;
		rs.mxs = max(a.mxs, b.mx);
	}else{
		rs.mxc = b.mxc;
		rs.mxs = max(a.mx, b.mxs);
	}

	rs.mn = min(a.mn, b.mn);
	if(a.mn == b.mn){
		rs.mnc = a.mnc + b.mnc;
		rs.mns = min(a.mns, b.mns);
	}else if(a.mn < b.mn){
		rs.mnc = a.mnc;
		rs.mns = min(a.mns, b.mn);
	}else{
		rs.mnc = b.mnc;
		rs.mns = min(a.mn, b.mns);
	}

	return rs;
}

struct segment_tree_beats{
	// ADD CHMAX CHMIN 1 2 3
	node st[4 * MX];

	bool break_condition(int nd, int val, int tp){
		if(tp == 1) return false;
		if(tp == 2) return st[nd].mn >= val;
		if(tp == 3) return st[nd].mx <= val;
		assert(0);
	}

	bool tag_condition(int nd, int val, int tp){
		if(tp == 1) return true;
		if(tp == 2) return st[nd].mns > val;
		if(tp == 3) return st[nd].mxs < val;
		assert(0);
	}

	void tag(int nd, int cl, int cr, int v, int tp){
		if(tp == 1){
			st[nd].sum += (cr - cl + 1) * 1ll * v;
			st[nd].lz += v;
			st[nd].mn += v; st[nd].mns += v;
			st[nd].mx += v; st[nd].mxs += v;
		}else if(tp == 2){
			st[nd].sum += (v - st[nd].mn) * 1ll * st[nd].mnc;
			if(st[nd].mx == st[nd].mn) st[nd].mx = v;
			if(st[nd].mxs == st[nd].mn) st[nd].mxs = v;
			st[nd].mn = v;
		}else if(tp == 3){
			st[nd].sum += (v - st[nd].mx) * 1ll * st[nd].mxc;
			if(st[nd].mn == st[nd].mx) st[nd].mn = v;
			if(st[nd].mns == st[nd].mx) st[nd].mns = v;
			st[nd].mx = v;
		}
	}

	void prop(int nd, int cl, int cr){
		if(cl != cr){
			tag(nd * 2, cl, (cl + cr) / 2, st[nd].lz, 1);
			tag(nd * 2 + 1, (cl + cr) / 2 + 1, cr, st[nd].lz, 1);
			st[nd].lz = 0;

			if(!break_condition(nd * 2, st[nd].mn, 2))
				tag(nd * 2, cl, (cl + cr) / 2, st[nd].mn, 2);
			if(!break_condition(nd * 2 + 1, st[nd].mn, 2))
				tag(nd * 2 + 1, (cl + cr) / 2 + 1, cr, st[nd].mn, 2);

			if(!break_condition(nd * 2, st[nd].mx, 3))
				tag(nd * 2, cl, (cl + cr) / 2, st[nd].mx, 3);
			if(!break_condition(nd * 2 + 1, st[nd].mx, 3))
				tag(nd * 2 + 1, (cl + cr) / 2 + 1, cr, st[nd].mx, 3);
		}
	}

	void build(int nd, int cl, int cr, int arr){
		if(cl == cr) return void(st[nd] = node(arr));

		build(nd * 2, cl, (cl + cr) / 2, arr);
		build(nd * 2 + 1, (cl + cr) / 2 + 1, cr, arr);
		st[nd] = merge(st[nd * 2], st[nd * 2 + 1]);
	}

	void upd(int nd, int cl, int cr, int lf, int rg, int v, int tp){
		if(rg < cl || cr < lf || break_condition(nd, v, tp)) return;
		if(lf <= cl && cr <= rg && tag_condition(nd, v, tp))
			return void(tag(nd, cl, cr, v, tp));

		prop(nd, cl, cr);
		upd(nd * 2, cl, (cl + cr) / 2, lf, rg, v, tp);
		upd(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg, v, tp);
		st[nd] = merge(st[nd * 2], st[nd * 2 + 1]);
	}

	ll que(int nd, int cl, int cr, int lf, int rg){
		if(rg < cl || cr < lf) return 0;
		if(lf <= cl && cr <= rg) return st[nd].sum;

		prop(nd, cl, cr);
		return que(nd * 2, cl, (cl + cr) / 2, lf, rg)
		 + que(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg);
	}

	void print(int nd, int cl, int cr){
		cout << nd << " " << st[nd].sum << endl;
		if(cl == cr) return;
		print(nd * 2, cl, (cl + cr) / 2);
		print(nd * 2 + 1, (cl + cr) / 2 + 1, cr);
	}
};
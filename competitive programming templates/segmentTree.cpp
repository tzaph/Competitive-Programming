#include <bits/stdc++.h>
using namespace std;

const int MX = 3e5 + 5;
int n, arr[MX];

struct segmentTree{
	struct node{ // nodenya apa aja
		// EXAMPLE HERE: POINT ADD UPDATE RANGE SUM QUERY
		int sum;

		node(int val = 0) : sum(val){}
	} identity;

	node merge(node lf, node rg){ // mergenya gimana
		// EXAMPLE HERE: POINT ADD UPDATE RANGE SUM QUERY
		node rs;
		rs.sum = lf.sum + rg.sum;
		return rs;
	}

	node st[2 * MX];

	#define md (cl + cr) / 2
	#define lc nd + 1
	#define rc nd + 2 * (md - cl + 1)

	void build(int nd, int cl, int cr){
		if(cl == cr) return void(st[nd].sum = arr[cl]);
		build(lc, cl, md);
		build(rc, md + 1, cr);
		st[nd] = merge(st[lc], st[rc]);
	}

	void upd(int nd, int cl, int cr, int id, int val){
		if(id < cl || cr < id) return;
		if(cl == cr && cl == id) return void(st[nd].sum += val); // EXAMPLE HERE: POINT ADD UPDATE

		upd(lc, cl, md, id, val);
		upd(rc, md + 1, cr, id, val);
		st[nd] = merge(st[lc], st[rc]);
	}

	void update(int ps, int val){
		return upd(1, 0, n - 1, ps, val);
	}

	node que(int nd, int cl, int cr, int lf, int rg){
		if(rg < cl || cr < lf) return identity;
		if(lf <= cl && cr <= rg) return st[nd];

		node L = que(lc, cl, md, lf, rg);
		node R = que(rc, md + 1, cr, lf, rg);
		return merge(L, R);
	}

	int query(int lf, int rg){
		return que(1, 0, n - 1, lf, rg).sum;
	}
};
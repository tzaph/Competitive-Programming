#include <iostream>
#include <vector>
using namespace std;
#define ll long long
const int MX = 100005;

class segTree{
	ll st[MX * 4], lz[MX * 4];

	void prop(int nd, int cl, int cr){
		if(lz[nd]){
			st[nd] += lz[nd];
			if(cl != cr){
				lz[nd * 2] += lz[nd];
				lz[nd * 2 + 1] += lz[nd];
			}
			lz[nd] = 0;
		}
	}

	void upd(int nd, int cl, int cr, int lf, int rg, ll val){
		prop(nd, cl, cr);
		if(lf > rg || rg < cl || cr < lf) return;
		if(lf <= cl && cr <= rg){
			lz[nd] += val;
			prop(nd, cl, cr);
			return;
		}

		upd(nd * 2, cl, (cl + cr) / 2, lf, rg, val);
		upd(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg, val);
		st[nd] = st[nd * 2] + st[nd * 2 + 1];
	}

	ll que(int nd, int cl, int cr, int lf, int rg){
		prop(nd, cl, cr);
		if(lf > rg || rg < cl || cr < lf) return 0;
		if(lf <= cl && cr <= rg) return st[nd];

		return
			que(nd * 2, cl, (cl + cr) / 2, lf, rg) +
			que(nd * 2 + 1, (cl + cr) / 2 + 1, cr, lf, rg);
	}
};
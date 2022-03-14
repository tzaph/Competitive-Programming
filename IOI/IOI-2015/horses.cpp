#include "horses.h"
#include <math.h>
using namespace std;
#define ld double
const int mod = 1e9 + 7;

int n;
struct node{
	int x, y, cost;
	ld lgx, lgy, lgcost;
}st[500005 * 4];

void upd(int nd, int cl, int cr, int ps, int x, int y){
	if(cr < ps || ps < cl) return;
	if(cl == cr && cl == ps){
		if(x){
			st[nd].lgx = log10(x);
			st[nd].x = x;
			st[nd].lgcost = st[nd].lgx + st[nd].lgy;
		}
		if(y){
			st[nd].lgy = log10(y);
			st[nd].y = y;
			st[nd].lgcost = st[nd].lgx + st[nd].lgy;
		}
		st[nd].cost = (st[nd].x * 1ll * st[nd].y) % mod;
		return;
	}

	upd(nd * 2, cl, (cl + cr) / 2, ps, x, y);
	upd(nd * 2 + 1, (cl + cr) / 2 + 1, cr, ps, x, y);

	st[nd].lgx = st[nd * 2].lgx + st[nd * 2 + 1].lgx;
	st[nd].x = (st[nd * 2].x * 1ll * st[nd * 2 + 1].x) % mod;

	if(st[nd * 2].lgcost < st[nd * 2 + 1].lgcost + st[nd * 2].lgx){
		st[nd].lgcost = st[nd * 2 + 1].lgcost + st[nd * 2].lgx;
		st[nd].cost = (st[nd * 2 + 1].cost * 1ll * st[nd * 2].x) % mod;
	}else{
		st[nd].lgcost = st[nd * 2].lgcost;
		st[nd].cost = st[nd * 2].cost;
	}

	return;
}

int init(int N, int X[], int Y[]){
	n = N;
	for(int i = 0; i < n; i ++)
		upd(1, 0, n - 1, i, X[i], Y[i]);
	return st[1].cost;
}

int updateX(int pos, int val){	
	upd(1, 0, n - 1, pos, val, 0);
	return st[1].cost;
}

int updateY(int pos, int val){
	upd(1, 0, n - 1, pos, 0, val);
	return st[1].cost;
}
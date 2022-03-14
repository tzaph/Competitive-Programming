#include "game.h"
#include <stdio.h>
using namespace std;

#define ll long long

int min(int x, int y){
	if(x > y) return y;
	return x;
}
int max(int x, int y){
	if(x < y) return y;
	return x;
}

int r, c;

ll gcd2(ll X, ll Y){
	ll tmp;
	while(X != Y && Y != 0){
		tmp = X;
		X = Y;
		Y = tmp % Y;
	}
	return X;
}

struct st_y{
	st_y *cl, *cr;
	int y;
	ll val;

	st_y(int ps) : cl(NULL), cr(NULL), y(ps), val(0){}
};

struct st_x{
	st_x *cl, *cr;
	st_y *cy;
	ll val;
};

st_x *root;

void init(int R, int C){
	root = new st_x();
	r = R, c = C;
}

void upd_y(st_y *nd, int cl, int cr, int y, ll v){
	int md = (cl + cr) / 2;
	if(nd -> y){
		if(nd -> y == y){
			nd -> val = v;
			return;
		}

		if(nd -> y <= md){
			nd -> cl = new st_y(nd -> y);
			nd -> cl -> val = nd -> val;
		}else{
			nd -> cr = new st_y(nd -> y);
			nd -> cr -> val = nd -> val;
		}

		nd -> y = 0;
	}

	if(y <= md){
		if(!nd -> cl)
			nd -> cl = new st_y(y);
		upd_y(nd -> cl, cl, md, y, v);
	}else{
		if(!nd -> cr)
			nd -> cr = new st_y(y);
		upd_y(nd -> cr, md + 1, cr, y, v);
	}

	ll v1 = 0; if(nd -> cl) v1 = nd -> cl -> val;
	ll v2 = 0; if(nd -> cr) v2 = nd -> cr -> val;
	nd -> val = gcd2(v1, v2);

	return;
}

ll find(st_y *nd, int cl, int cr, int y){
	if(!nd) return 0;
	if(nd -> y){
		if(nd -> y == y) return nd -> val;
		return 0;
	}

	int md = (cl + cr) / 2;
	if(y <= md) return find(nd -> cl, cl, md, y);
	else return find(nd -> cr, md + 1, cr, y);
}

void upd_x(st_x *nd, int cl, int cr, int x, int y, ll v){
	if(!nd -> cy) nd -> cy = new st_y(y);
	if(cl == cr)
		return void(upd_y(nd -> cy, 1, c, y, v));
	
	int md = (cl + cr) / 2;
	if(!nd -> cl) nd -> cl = new st_x();
	if(!nd -> cr) nd -> cr = new st_x();

	if(x <= md) upd_x(nd -> cl, cl, md, x, y, v);
	else upd_x(nd -> cr, md + 1, cr, x, y, v);

	ll rs = gcd2(
		find(nd -> cl -> cy, 1, c, y),
		find(nd -> cr -> cy, 1, c, y));

	upd_y(nd -> cy, 1, c, y, rs);
}

void update(int p, int q, ll k){
	upd_x(root, 1, r, p + 1, q + 1, k);
}

ll que_y(st_y *nd, int cl, int cr, int ly, int ry){
	if(!nd) return 0;
	if(nd -> y){
		if(ly <= nd -> y && nd -> y <= ry)
			return nd -> val;
		return 0;
	}

	if(cl == ly && cr == ry) return nd -> val;

	int md = (cl + cr) / 2;
	ll lf = 0ll, rg = 0ll;

	if(ly <= md && nd -> cl)
		lf = que_y(nd -> cl, cl, md, ly, min(md, ry));
	if(md + 1 <= ry && nd -> cr)
		rg = que_y(nd -> cr, md + 1, cr, max(ly, md + 1), ry);

	return gcd2(lf, rg);
}

ll que_x(st_x *nd, int cl, int cr, int lx, int ly, int rx, int ry){
	if(cl == lx && cr == rx)
		return que_y(nd -> cy, 1, c, ly, ry);

	int md = (cl + cr) / 2;
	ll lf = 0, rg = 0;

	if(lx <= md && nd -> cl)
		lf = que_x(nd -> cl, cl, md, lx, ly, min(rx, md), ry);
	if(md + 1 <= rx && nd -> cr)
		rg = que_x(nd -> cr, md + 1, cr, max(lx, md + 1), ly, rx, ry);

	return gcd2(lf, rg);
}

ll calculate(int P, int Q, int U, int V){
	return que_x(root, 1, r, P + 1, Q + 1, U + 1, V + 1);
}
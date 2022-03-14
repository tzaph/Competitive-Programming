#include "teams.h"
#include <vector>
#include <algorithm>
// #include <queue>
#include <stack>
using namespace std;

int n;
vector<int> sweep[500005];

int rt[500005], lf[20 * 500005], rg[20 * 500005], sum[20 * 500005], sz;

void upd(int bf, int &nd, int cl, int cr, int v){
	nd = ++ sz;
	lf[nd] = lf[bf]; rg[nd] = rg[bf]; sum[nd] = sum[bf] + 1;
	if(cl == cr) return;

	if(v <= (cl + cr) / 2)
		upd(lf[bf], lf[nd], cl, (cl + cr) / 2, v);
	else
		upd(rg[bf], rg[nd], (cl + cr) / 2 + 1, cr, v);
}

int que(int bf, int nd, int cl, int cr, int ql, int qr){
	if(qr < cl || cr < ql || cl > cr || ql > qr) return 0;
	if(ql <= cl && cr <= qr) return sum[nd] - sum[bf];
	return que(lf[bf], lf[nd], cl, (cl + cr) / 2, ql, qr) + que(rg[bf], rg[nd], (cl + cr) / 2 + 1, cr, ql, qr);
}

int find(int bf, int nw, int cl, int cr, int val){
	if(cl == cr) return cl;
	if(sum[lf[nw]] - sum[lf[bf]] >= val)
		return find(lf[bf], lf[nw], cl, (cl + cr) / 2, val);
	else
		return find(rg[bf], rg[nw], (cl + cr) / 2 + 1, cr, val - (sum[lf[nw]] - sum[lf[bf]]));
}

void init(int N, int A[], int B[]){
	n = N;
	for(int i = 0; i < n; i ++)
		sweep[A[i]].push_back(B[i]);

	for(int i = 1; i <= n; i ++){
		rt[i] = rt[i - 1];
		for(int x : sweep[i])
			upd(rt[i], rt[i], 1, n, x);
	}
}

int val[500005], cnt[500005], used[500005];
int x[500005], y[500005], vv[500005], top;
int can(int M, int K[]){
	sort(K, K + M);
	int sum = 0, id = 0;
	for(int i = 0; i < M; i ++){
		sum += K[i];
		if(id > 0 && val[id - 1] == K[i])
			cnt[id - 1] += K[i];
		else
			val[id] = cnt[id] = K[i], id ++;
	}
	if(sum > n) return 0;

	top = 0;
	x[top] = 0, y[top] = n, vv[top] = 0; top ++;

	for(int i = 0; i < id; i ++){
		int need = cnt[i];
		while(top && y[top - 1] < val[i]) top --;
		int last = val[i] - 1;
		while(top){
			int add = que(rt[x[top - 1]], rt[val[i]], 1, n, last + 1, y[top - 1]) + vv[top - 1];
			if(add < need) need -= add;
			else break;
			last = y[top - 1]; top --;
		}
		if(!top) return 0;

		int t = find(rt[x[top - 1]], rt[val[i]], 1, n, need + que(rt[x[top - 1]], rt[val[i]], 1, n, 1, last));
		t = min(t, y[top - 1]);
		x[top] = val[i];
		y[top] = t;
		vv[top] = que(rt[x[top - 1]], rt[val[i]], 1, n, last + 1, t) - need;
		top ++;
	}

	return 1;
}
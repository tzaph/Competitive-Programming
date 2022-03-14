#include "seats.h"
#include <bits/stdc++.h>
using namespace std;

#define mx(a, b) (a > b ? a : b)
#define mn(a, b) (a < b ? a : b)
#define ll long long
const int inf = 2;
const int MX = 1000005;
const int dx[] = {1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1};

int mn[MX * 4], lz[MX * 4];
int cnt[MX * 4];
int sz;

void merge(int m, int l, int r){
	if(mn[l] < mn[r]){
		mn[m] = mn[l];
		cnt[m] = cnt[l];
	}else if(mn[l] > mn[r]){
		mn[m] = mn[r];
		cnt[m] = cnt[r];
	}else{
		mn[m] = mn[l];
		cnt[m] = cnt[l] + cnt[r];
	}
}

vector<int> arr;
void build(int nd, int cl, int cr){
	if(cl == cr){
		mn[nd] = arr[cl];
		cnt[nd] = 1;
		return;
	}
	build(nd * 2, cl, (cl + cr) / 2);
	build(nd * 2 + 1, (cl + cr) / 2 + 1, cr);
	merge(nd, nd * 2, nd * 2 + 1);
}

void init(int a){
	sz = a;
	build(1, 0, sz - 1);
}

void prop(int nd, int cl, int cr){
	if(lz[nd]){
		mn[nd] += lz[nd];
		if(cl != cr){
			lz[nd * 2] += lz[nd];
			lz[nd * 2 + 1] += lz[nd];
		}
		lz[nd] = 0;
	}
}

int ul, ur, uv;
void upd(int nd, int cl, int cr){
	prop(nd, cl, cr);
	if(ur < cl || cr < ul) return;
	if(ul <= cl && cr <= ur){
		lz[nd] += uv;
		prop(nd, cl, cr);
		return;
	}

	upd(nd * 2, cl, (cl + cr) / 2);
	upd(nd * 2 + 1, (cl + cr) / 2 + 1, cr);

	merge(nd, nd * 2, nd * 2 + 1);
}
void upd(){
	if(ul > ur) return;
	upd(1, 0, sz - 1);
}

void dfs(int nd, int cl, int cr){
	if(cl == cr){
		cout << mn[nd] << " ";
		return;
	}

	dfs(nd * 2, cl, (cl + cr) / 2);
	dfs(nd * 2 + 1, (cl + cr) / 2 + 1, cr);
}
void print(){
	dfs(1, 0, sz - 1); cout << endl;
}

int h, w, ans;
vector<int> r, c;
vector<vector<int> > mp;

void give_initial_chart(int H, int W, vector<int> R, vector<int> C){
	r = R; c = C;
	h = H; w = W;

	mp.assign(h + 2, vector<int>(w + 2, r.size()));
	for(int i = 0; i < r.size(); i ++){
		r[i] ++; c[i] ++;
		mp[r[i]][c[i]] = i;
	}

	arr.resize(r.size() + 1);
	for(int i = 0; i <= h; i ++)
		for(int j = 0; j <= w; j ++){
			vector<int> ord = {mp[i][j], mp[i + 1][j], mp[i][j + 1], mp[i + 1][j + 1]};
			sort(ord.begin(), ord.end());

			arr[ord[0]] ++; arr[ord[1]] --;
			arr[ord[2]] += inf; arr[ord[3]] -= inf;
		}

	for(int i = 0; i <= r.size(); i ++)
		arr[i] += (i > 0 ? arr[i - 1] : 0);

	init(r.size());

	return;
}

int swap_seats(int a, int b){
	vector<int> li = {a, b};
	set<pair<int, int> > processed;
	for(int x, y, tp = 0; tp < 2; tp ++){
		x = r[li[tp]], y = c[li[tp]];
		for(int d = 0; d < 4; d ++){
			int mnr = min(x, x + dx[d]);
			int mnc = min(y, y + dy[d]);
			if(processed.count({mnr, mnc})) continue;
			processed.insert({mnr, mnc});
			if(mnr < 0 || mnc < 0) continue;
			if(x + dx[d] > h + 1 || y + dy[d] > w + 1 ) continue;

			vector<int> ord = {mp[x][y], mp[x + dx[d]][y], mp[x][y + dy[d]], mp[x + dx[d]][y + dy[d]]};
			sort(ord.begin(), ord.end());

			ul = ord[0], ur = ord[1] - 1, uv = -1;
			upd();
			ul = ord[2], ur = ord[3] - 1, uv = -inf;
			upd();
		}
	}

	swap(mp[r[a]][c[a]], mp[r[b]][c[b]]);
	swap(r[a], r[b]);
	swap(c[a], c[b]);

	processed.clear();
	for(int x, y, tp = 0; tp < 2; tp ++){
		x = r[li[tp]], y = c[li[tp]];
		for(int d = 0; d < 4; d ++){
			int mnr = min(x, x + dx[d]);
			int mnc = min(y, y + dy[d]);
			if(processed.count({mnr, mnc})) continue;
			processed.insert({mnr, mnc});
			if(mnr < 0 || mnc < 0) continue;
			if(x + dx[d] > h + 1 || y + dy[d] > w + 1) continue;
			vector<int> ord = {mp[x][y], mp[x + dx[d]][y], mp[x][y + dy[d]], mp[x + dx[d]][y + dy[d]]};
			sort(ord.begin(), ord.end());

			ul = ord[0], ur = ord[1] - 1, uv = 1;
			upd();
			ul = ord[2], ur = ord[3] - 1, uv = inf;
			upd();
		}
	}	

	return cnt[1];
}
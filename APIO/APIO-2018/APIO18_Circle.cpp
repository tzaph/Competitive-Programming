#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n, cr = 2000000069, id[300005];
vector<int> ans;
unordered_map<ll, vector<int> >grid;

ll sqr(ll x){return x *1ll* x;}

struct circ{int x, y, r;} a[300005];
bool intersect(circ aa, circ b){return sqr(aa.x - b.x) + sqr(aa.y - b.y) <= sqr(aa.r + b.r);}

void build(int sz){
	grid.clear();
	for(int i = 1; i <= n; i ++) if(!ans[i]){
		int cx = a[i].x / sz, cy = a[i].y / sz;
		grid[cx * 2000000069ll + cy].push_back(i);
	}
	return;
}

void solve(ll ps, int nw){
	if(!grid.count(ps)) return;

	for(int i = 0; i < grid[ps].size(); i ++){
		if(intersect(a[grid[ps][i]], a[nw])){
			ans[grid[ps][i]] = nw;
			swap(grid[ps][i--], grid[ps].back());
			grid[ps].pop_back();
		}
	}

	if(grid[ps].empty()) grid.erase(ps);
	return;
}

bool cmp(int i, int j){
	if(a[i].r == a[j].r)
		return i < j;
	return a[i].r > a[j].r;
}

int main(){
	scanf("%d", &n);
	ans.resize(n + 1);
	for(int i = 1; i <= n; i ++){
		scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].r);
		id[i] = i;
		a[i].x += 1000000000; a[i].y += 1000000000;
	}
	sort(id + 1, id + n + 1, cmp);

	for(int i = 1; i <= n; i ++) if(!ans[id[i]]){
		int nw = id[i];
		if(a[nw].r <= cr / 2){
			cr = a[nw].r;
			build(cr);
		}
		int nwx = a[nw].x / cr, nwy = a[nw].y / cr;
		for(int nxx = nwx - 2; nxx <= nwx + 2; nxx ++)
			for(int nxy = nwy - 2; nxy <= nwy + 2; nxy ++)
				solve(nxx * 2000000069ll + nxy, nw);
	}

	for(int i = 1; i <= n; i ++)
		printf("%d%c", ans[i], (i == n ? '\n' : ' '));
	return 0;
}
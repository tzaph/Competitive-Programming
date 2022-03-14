#include "rect.h"
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

vector<int> row[2505], col[2505];
int n, m, fwt[2505];
int lr[2505][2505], cr[2505][2505];
int lc[2505][2505], cc[2505][2505];

void upd(int ps, int v){
	for(; ps < 2505; ps += ps & -ps)
		fwt[ps] += v;
}
int que(int ps){
	int rs = 0;
	for(; ps > 0; ps -= ps & -ps)
		rs += fwt[ps];
	return rs;
}

pair<int, int> get_row(int l, int r, int cr_){
	if(lr[l][r] != cr_ - 1) cr[l][r] = 0;
	cr[l][r] ++; lr[l][r] = cr_;
	return {r - l - 1, cr[l][r]};
}
pair<int, int> get_col(int l, int r, int cr_){
	if(lc[l][r] != cr_ - 1) cc[l][r] = 0;
	cc[l][r] ++; lc[l][r] = cr_;
	return {r - l - 1, cc[l][r]};
}

ll solve(vector<pair<int, int> > pr, vector<pair<int, int> > pc){
	ll rs = 0ll;
	for(auto &i : pc) swap(i.first, i.second);
	sort(pr.rbegin(), pr.rend());
	sort(pc.rbegin(), pc.rend());

	int ps = 0;
	for(auto i : pr){
		for(; ps < pc.size() && i.first <= pc[ps].first; ps ++)
			upd(pc[ps].second, 1);
		rs += que(i.second);
	}
	for(int i = 0; i < ps; i ++)
		upd(pc[i].second, -1);

	return rs;
}

ll count_rectangles(vector<vector<int> > a){
	n = a.size(), m = a[0].size();
	for(int i = 0; i < n; i ++) row[i] = {0};
	for(int i = 0; i < m; i ++) col[i] = {0};

	ll ans = 0ll;
	
	for(int i = 0; i < n - 1; i ++) for(int j = 0; j < m - 1; j ++){
		bool eq = false;
		vector<pair<int, int> > pr;
		for(; row[i].size();){
			int nw = row[i].back();
			if(nw < j && !eq)
				pr.push_back(get_row(nw, j + 1, i));
			if(a[i][nw] <= a[i][j + 1]){
				if(a[i][nw] == a[i][j + 1]) eq = true;
				row[i].pop_back();
			}else break;
		}
		row[i].push_back(j + 1);

		eq = false;
		vector<pair<int, int> > pc;
		for(; col[j].size();){
			int nw = col[j].back();
			if(nw < i && !eq)
				pc.push_back(get_col(nw, i + 1, j));
			if(a[nw][j] <= a[i + 1][j]){
				if(a[nw][j] == a[i + 1][j]) eq = true;
				col[j].pop_back();
			}else break;
		}
		col[j].push_back(i + 1);

		ans += solve(pr, pc);
	}

	return ans;
}
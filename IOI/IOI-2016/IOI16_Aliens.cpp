#include "aliens.h"
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

#define ll long long
#define ld long double
const int MX = 100005;
const ll inf = 1e15;

ll sq(ll x){return x * 1ll * x;}
vector<pair<ll, ll> > v;

struct line{
	ll a, b, c;
};
deque<line> cht;

void add(ll a, ll b, ll c){
	while(cht.size() >= 2){
		ll cdi = (cht.back().b - cht[cht.size() - 2].b) * (cht.back().a - a);
		ll cdj = (b - cht.back().b) * 1ll * (cht[cht.size() - 2].a - cht.back().a);

		if(cdi > cdj || (cdi == cdj && cht.back().c > c))
			cht.pop_back();
		else break;
	}

	cht.push_back((line){a, b, c});
}

pair<ll, int> que(ll x){
	while(cht.size() >= 2){
		ll ei = cht.front().a * x + cht.front().b;
		ll ej = cht[1].a * x + cht[1].b;

		if(ei > ej || (ei == ej && cht.front().c > cht[1].c))
			cht.pop_front();
		else break;
	}

	return make_pair(cht.front().a * x + cht.front().b, cht.front().c);
}

pair<ll, int> get(ll r){
	pair<ll, int> dp = {0, 0};
	cht.clear();
	for(int i = 0; i < v.size(); i ++){
		ll d1;
		if(i) d1 = max(0ll, v[i - 1].first - v[i].second + 1);
		else d1 = 0ll;
		ll d2 = v[i].second;

		add(-2ll * d2, dp.first - sq(d1) + sq(d2), dp.second);

		dp = que(v[i].first + 1);
		dp.first += sq(v[i].first + 1) + r;
		dp.second ++;
	}

	return dp;
}

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c){
	for(int i = 0; i < n; i ++){
		if(r[i] < c[i]) swap(r[i], c[i]);
		v.push_back({r[i], c[i]});
	}
	sort(v.begin(), v.end());

	vector<pair<ll, ll> > tmp;
	for(int i = 0; i < n; i ++){
		while(!tmp.empty() && v[i].second <= tmp.back().second)
			tmp.pop_back();
		tmp.push_back(v[i]);
	}
	v = tmp;

	ll lf = 0, rg = m * 1ll * m, ans;
	for(ll md; lf <= rg;){
		md = (lf + rg) / 2ll;
		pair<ll, int> rs = get(md);
		if(rs.second <= k){
			ans = rs.first;
			rg = md - 1;
		}else lf = md + 1;
	}

	return ans - lf * 1ll * k;
}
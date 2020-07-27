/*
	* LMIO 2019 Wish
	* Check when each star passes through the circle
	* Produce the formula, to prevent precision problems
	* Do binary search/ternary search as well as
	* Floor division and ceiling division described in the code
	* Using __int128_t to prevent overflow
	* Find maximum number of intervals at a time by using prefix sum
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#define ll __int128_t
#define ld long double

ll floor_division(ll a, ll b){
	return a / b - (a % b < 0);
}
ll ceiling_division(ll a, ll b){
	return a / b + (a % b > 0);
}

ll ll_sqrt(ll x){
	ll lf = 0ll, rg = 1000000000000000000ll, res;
	for(ll md; lf <= rg;){
		md = (lf + rg) / 2;
		if(md == 0){
			res = 0ll;
			lf = 1ll;
			continue;
		}
		if(md > x / md) rg = md - 1;
		else{
			res = md;
			lf = md + 1;
		}
	}

	return res;
}

int n;
ll r, a, b, c, d;
vector<pair<ll, int> > pref;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	long long tmp;
	cin >> n >> tmp; r = (ll)tmp;
	for(int i = 1; i <= n; i ++){
		cin >> tmp; a = (ll)tmp;
		cin >> tmp; b = (ll)tmp;
		cin >> tmp; c = (ll)tmp;
		cin >> tmp; d = (ll)tmp;

		c -= a; d -= b;

		ll A = c * c + d * d;
		ll B = 2ll * a * c + 2ll * b * d;
		ll C = a * a + b * b - r * r;

		ll D = B * B - 4ll * A * C;
		if(D < 0) continue;

		ll sqD = ll_sqrt(D);
		ll lf = ceiling_division(- B - sqD, 2ll * A);
		ll rg = floor_division(- B + sqD, 2ll * A);
		if(lf < 0) lf = 0;

		if(lf > rg) continue;
		pref.push_back({lf, 1});
		pref.push_back({rg + 1ll, -1});
	}

	if(pref.empty()){
		cout << 0 << endl;
		return 0;
	}

	sort(pref.begin(), pref.end());

	int cnt = pref[0].second, ans = 0;
	ll lst = pref[0].first;
	for(int i = 1; i < pref.size(); i ++){
		if(lst != pref[i].first){
			ans = max(ans, cnt);
			lst = pref[i].first;
		}
		cnt += pref[i].second;
	}
	ans = max(ans, cnt);

	cout << ans << endl;
	return 0;
}
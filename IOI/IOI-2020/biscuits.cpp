#include "biscuits.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

unordered_map<ll, ll> dp;
ll x, pref[100];

ll f(ll n){
	if(n <= 0) return 0;
	if(n == 1) return 1;
	if(dp.count(n)) return dp[n];

	ll tmp = n - 1; int cnt = 0;
	for(; tmp > 0; tmp /= 2, cnt ++);
	cnt --;
	dp[n] = f(1ll << cnt) + f(min(n, 1 + pref[cnt] / x) - (1ll << cnt));
	return dp[n];
}

ll count_tastiness(ll X, vector<ll> a){
	x = X; dp.clear();
	for(int i = 0; i < a.size(); i ++)
		pref[i] = a[i];
	for(int i = 1; i < a.size(); i ++)
		pref[i] = pref[i - 1] + (pref[i] << i);
	for(int i = a.size(); i <= 60; i ++)
		pref[i] = pref[i - 1];
	return f(1 + pref[60]);
}
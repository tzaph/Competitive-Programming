#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MX = 100005;
const ll mod = 998244353;
const ll root = 3;

ll pw(ll b, ll e){
	b %= mod; ll r = 1ll;
	for(; e > 0; e /= 2, (b *= b) %= mod)
		if(e % 2) (r *= b) %= mod;
	return r;
}

using poly = vector<ll>;

void ntt(poly &a, vector<ll> &roots, bool inv = false){
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i ++){
		int bt = n / 2;
		for(; j & bt; j ^= bt, bt /= 2);
		j ^= bt;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 1; len < n; len *= 2){
		for(int i = 0; i < n; i += 2 * len)
			for(int j = 0; j < len; j ++){
				ll u = a[i + j];
				ll v = (a[i + j + len] * roots[n / 2 / len * j]) % mod;
				a[i + j] = (u + v) % mod;
				a[i + j + len] = (u + mod - v) % mod;
			}
	}

	if(inv){
		ll d = pw(n, mod - 2);
		for(auto &i : a) (i *= d) %= mod;
	}
}

poly add(poly a, poly b){
	if(a.size() < b.size()) swap(a, b);
	for(int i = 0; i < b.size(); i ++)
		a[i] += b[i];
	return a;
}

poly subtract(poly a, poly b){
	if(a.size() < b.size()) a.resize(b.size());
	for(int i = 0; i < b.size(); i ++) a[i] -= b[i];
	return a;
}

poly multiply(poly a, poly b){
	if(a.empty() || b.empty()) return {};

	int sz = a.size() + b.size() - 1;
	int n = 1; for(; n < sz; n *= 2);

	vector<ll> roots(n);
	roots[0] = 1ll, roots[1] = pw(root, (mod - 1) / n);
	for(int i = 2; i < n; i ++)
		roots[i] = (pw(roots[i / 2], 2) * 1ll * roots[i % 2]) % mod;

	a.resize(n); ntt(a, roots);
	b.resize(n); ntt(b, roots);
	for(int i = 0; i < n; i ++)
		(a[i] *= b[i]) %= mod;
	for(int i = 1; 2 * i < n; i ++)
		swap(roots[i], roots[n - i]);
	ntt(a, roots, 1);
	a.resize(sz);
	return a;
}
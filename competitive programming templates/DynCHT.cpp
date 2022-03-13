#include <iostream>
#include <set>
#include <limits.h>
using namespace std;
//this is Maximum CHT
//for minimum, reverse comparator or just use y = -mx - c
#define ll long long

bool Q;
struct Line{
	mutable ll m, c, pt;
	bool operator<(const Line& rhs) const{
		return Q ? pt < rhs.pt : m < rhs.m;
	}
};
 
struct LineContainer : multiset<Line>{
	const ll inf = LLONG_MAX;

	ll div(ll a, ll b){
		return a / b - ((a ^ b) < 0 && a % b);
	}

	bool isect(iterator a, iterator b){
		if(b == end()){
			a -> pt = inf;
			return false;
		}

		if(a -> m == b -> m) a -> pt = a -> c > b -> c ? inf : -inf;
		else a -> pt = div(b -> c - a -> c, a -> m - b -> m);
		return a -> pt >= b -> pt;
	}

	void add(ll m, ll c){
		auto z = insert({m, c, 0}), y = z ++, x = y;
		while(isect(y, z)) z = erase(z);
		if(x != begin() && isect(-- x, y)) isect(x, y = erase(y));
		while((y = x) != begin() && (-- x) -> pt >= y -> pt)
			isect(x, erase(y));
	}

	ll que(ll x){
		Q = 1; auto l = *lower_bound({0, 0, x}); Q = 0;
		return l.m * 1ll * x + l.c;
	}
} cht;

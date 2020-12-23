#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

struct FenwickTree{
	int N;
	vector<ll> fwt;

	FenwickTree(){N = 0; fwt.clear();}
	void resize(int n){
		N = n; fwt.resize(N + 1);
	}

	void upd(int ps, ll x){
		for(; ps <= N; ps += ps & -ps)
			fwt[ps] += x;
	}
	void updrange(int l, int r, int x){ //prefix diff
		upd(l, x); upd(r + 1, -x);
	}

	int que(int ps){
		int res = 0;
		for(; ps > 0; ps -= ps & -ps)
			res += fwt[ps];
		return res;
	}

	int lower_bound(ll x){
		if(x <= 0) return -1; //empty
		int ps = 0;
		for(int cr = (1 << 25); cr; cr >>= 1){
			if(ps + cr <= N && fwt[ps + cr - 1] < x)
				ps += cr, x -= fwt[ps - 1];
		}
		return ps;
	}
};

struct FenwickTree2D{
	int N;
	vector<vector<int> > cc;
	vector<FenwickTree> fwt;

	FenwickTree2D(){N = 0; fwt.clear();}
	FenwickTree2D(int n){N = n; resize(n);}

	void resize(int n){
		N = n;
		fwt.resize(n + 1);
		cc.resize(n + 1);
	}

	void build(){
		for(int i = 1; i <= N; i ++){
			sort(cc[i].begin(), cc[i].end());
			cc[i].erase(unique(cc[i].begin(), cc[i].end()), cc[i].end());
			fwt[i].resize(cc[i].size());
		}
	}

	void insert_query_interval(int ps, int x){
		for(; ps > 0; ps -= ps & -ps)
			cc[ps].push_back(x);
	}

	void upd(int ps, int l, int r, int x){
		for(; ps <= N; ps += ps & -ps){
			int il = lower_bound(cc[ps].begin(), cc[ps].end(), l) - cc[ps].begin() + 1;
			int ir = prev(upper_bound(cc[ps].begin(), cc[ps].end(), r)) - cc[ps].begin() + 1;
			fwt[ps].updrange(il, ir, x);
		}
	}
	void updrange(int a, int b, int c, int d, int x){
		upd(a, c, d, x); upd(b + 1, c, d, -x);
	}

	int que(int psx, int psy){
		int res = 0;
		for(; psx > 0; psx -= psx & -psx){
			int id = prev(upper_bound(cc[psx].begin(), cc[psx].end(), psy)) - cc[psx].begin() + 1;
			res += fwt[psx].que(id);
		}
		return res;
	}
};
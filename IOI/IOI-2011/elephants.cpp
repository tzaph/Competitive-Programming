#include "elephants.h"
#include <bits/stdc++.h>
using namespace std;

const int MX = 150005;
const int BLOCK = 400;

int n, l;

struct Bucket{
	int sz, dp[2 * BLOCK], rang[2 * BLOCK], x[2 * BLOCK];
	
	Bucket() : sz(0){}

	void build(){
		for(int i = sz - 1, j = sz; i >= 0; i --){
			for(; j && x[i] + l < x[j - 1]; j --);
			if(j == sz)
				dp[i] = 1, rang[i] = x[i] + l;
			else
				dp[i] = dp[j] + 1, rang[i] = rang[j];
		}
	}

	void push(int y){
		x[sz ++] = y;
	}

	void add(int y){
		int lf = 0, rg = sz - 1, id = rg + 1;
		for(int md; lf <= rg;){
			md = (lf + rg) / 2;
			if(x[md] > y){
				id = md;
				rg = md - 1;
			}else{
				lf = md + 1;
			}
		}

		sz ++;
		for(int i = sz - 1; i > id; i --) 
			x[i] = x[i - 1];
		x[id] = y;

		build();
	}

	void del(int y){
		int lf = 0, rg = sz - 1, id = rg + 1;
		for(int md; lf <= rg;){
			md = (lf + rg) / 2;
			if(x[md] >= y){
				id = md;
				rg = md - 1;
			}else{
				lf = md + 1;
			}
		}

		sz --;
		for(int i = id; i < sz; i ++)
			x[i] = x[i + 1];

		build();
	}
} bk[BLOCK];

int cnt_op = 0;

void rebuild(){
	vector<int> tmp;
	for(int i = 0; i < BLOCK; i ++){
		for(int j = 0; j < bk[i].sz; j ++)
			tmp.push_back(bk[i].x[j]);
		bk[i].sz = 0;
	}

	for(int i = 0; i < tmp.size(); i ++)
		bk[i / BLOCK].push(tmp[i]);
	for(int i = 0; i < BLOCK; i ++)
		bk[i].build();

	cnt_op = 0;
}

int ps[MX];

void init(int N, int L, int X[]){
	n = N; l = L;
	for(int i = 0; i < n; i ++) ps[i] = X[i];

	for(int i = 0; i < n; i ++)
		bk[i / BLOCK].push(ps[i]);
	for(int i = 0; i < BLOCK; i ++)
		bk[i].build();
}

int update(int id, int y){
	for(int i = 0; i <= BLOCK; i ++){
		if(i == BLOCK || !bk[i].sz || bk[i].x[0] > ps[id]){
			if(i) i --;
			bk[i].del(ps[id]);
			break;
		}
	}

	ps[id] = y;

	for(int i = 0; i <= BLOCK; i ++){
		if(i == BLOCK || !bk[i].sz || bk[i].x[0] > ps[id]){
			if(i) i --;
			bk[i].add(ps[id]);
			break;
		}
	}

	int ans = 0, range = -1;
	for(int i = 0; i < BLOCK; i ++){
		if(!bk[i].sz) break;

		int j = upper_bound(bk[i].x, bk[i].x + bk[i].sz, range) - bk[i].x;
		if(j == bk[i].sz) continue;
		ans += bk[i].dp[j]; range = bk[i].rang[j];
	}

	cnt_op ++;
	if(cnt_op == BLOCK - 5) rebuild();
	return ans;
}
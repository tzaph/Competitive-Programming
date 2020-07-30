/*
	* APIO 2016 Gap

	* T = 1
	> Two pointers, left right approaching the center

	* T = 2
	> pigeon hole principle
	> get minimum and maximum, 
	> then divide the array into n - 1 approx. equal parts
	> By PHP, one of these parts will be empty
	> Thus, maximum gap >= the length of a part
	> Now we can simply compare with seg[i].left - seg[i - 1].right
*/
#include "gap.h"
#include <iostream>
using namespace std;

#define ll long long
const ll mn = 0ll, mx = 1e18;

ll res = mn, arr[100005];

ll findGap(int t, int n){
	if(t == 1){
		ll lf = mn, rg = mx, k = 0;
		for(int i = n; i > 0; i -= 2){
			MinMax(lf, rg, &arr[k], &arr[n - 1 - k]);
			lf = arr[k] + 1;
			rg = arr[n - 1 - k] - 1;
			k ++;
		}

		for(int i = 1; i < n; i ++)
			res = max(res, arr[i] - arr[i - 1]);
	}
	if(t == 2){
		ll lf, rg;
		MinMax(mn, mx, &lf, &rg);

		if(n == 2) return rg - lf;
		ll len = rg - lf - 1ll;	
		ll st = lf + 1, ed = lf;

		for(int i = 0; i < n - 1; i ++){
			ll e = st + len / (n - 1) - 1;
			if(i < len % (n - 1)) e ++;
			MinMax(st, e, &lf, &rg);

			if(lf != -1){
				res = max(res, lf - ed);
				ed = rg;
			}
			st = e + 1ll;
		}
		res = max(res, st - ed);
	}
	return res;
}

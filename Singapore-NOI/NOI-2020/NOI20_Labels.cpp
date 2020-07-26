/*
	* NOI 2020 A Labels
	* Set the first element as a variable X
	* Find the minimum and maximum in terms of x
	* If the difference is exactly N - 1, there is a unique solution
	* Solve for x and recreate the array
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
using namespace std;

#define ll long long
int n;
ll pref[300005];

void abrt(){
	printf("-1\n");
	exit(0);
}

int main(){
	scanf("%d", &n);
	ll mn = 0ll, mx = 0ll;
	pref[1] = 0ll;
	for(int x, i = 1; i < n; i ++){
		scanf("%d", &x);
		pref[i + 1] = pref[i] + (ll)x;
		mn = min(mn, pref[i + 1]);
		mx = max(mx, pref[i + 1]);
	}

	ll x = -1ll;
	if(mx - mn == n - 1){
		x = 1 - mn;
		if(x < 0) abrt();
		for(int i = 1; i <= n; i ++){
			printf("%lld", pref[i] + x);
			if(i == n) printf("\n");
			else printf(" ");
		}
		return 0;
	}
	abrt();
}
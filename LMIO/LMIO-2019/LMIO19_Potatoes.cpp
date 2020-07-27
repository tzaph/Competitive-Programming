/*
	* LMIO 2019 Potatoes and Fertilizers
	* a - b shows the number of fertilizers spared
	* Take the prefix sum of a - b
	* The problem becomes:
		- An operation allows increment 
		  or decrement an element by 1
		- Special case on the leftmost element
			> can't be decremented, must be non-negative
		- Special case on the rightmost element
			> can't be incremented
		- We want to make the array non-decreasing
	* This can be solved with slope trick
	* A similar problem: https://codeforces.com/contest/713/problem/C
	* More about slope trick: https://codeforces.com/blog/entry/77298
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

#define ll long long
int n;
ll pref[500005], a, b;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for(int i = 0; i < n; i ++){
		cin >> a >> b;
		pref[i] = a - b;
		if(i > 0)
			pref[i] += pref[i - 1];
	}

	ll ans = 0ll;
	priority_queue<ll> pq;
	pq.push(0ll);
	for(int i = 0; i < n; i ++){
		if(pref[i] < 0){
			ans += 0ll - pref[i];
			pref[i] = 0ll;
		}else if(pref[i] > pref[n - 1]){
			ans += pref[i] - pref[n - 1];
			pref[i] = pref[n - 1];
		}

		pq.push(pref[i]);
		pq.push(pref[i]);
		ans += pq.top() - pref[i];
		pq.pop();
	}

	cout << ans << endl;
	return 0;
}
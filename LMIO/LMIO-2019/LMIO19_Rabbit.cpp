/*
	* LMIO 2019 Rabbit Carrot
	* Subtract the array with i * m
	* A path is possible to cross if the array is
		- non increasing
		- starts with less than or equal to 0
	* Find the longest non-increasing subsequence
	* Alternatively additive inverse the array and
	* Find LNDS in NlogN
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
 
int n, m, v;
vector<int> dp; //longest non-decreasing subsequence
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
 
	cin >> n >> m;
 
	for(int i = 1; i <= n; i ++){
		cin >> v;
		v = i * m - v;
		if(v < 0) continue;
 
		int id = upper_bound(dp.begin(), dp.end(), v) - dp.begin();
		if(id == dp.size()) dp.push_back(v);
		else dp[id] = v;
	}
 
	cout << n - dp.size() << endl;
	return 0;
}
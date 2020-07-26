/*
	* NOI 2020 D Arcade
	* Plot the commands on a T vs A plane
	* Two points can be connected if the angle on respect to T axis
	* Is less than or equal to 45 degrees
	* Rotate the graph 45 degrees. 
	* Now two points can be connected if one is at the bottom left of another
	* Make a directed acyclic graph, fine minimum number of chains
	* Dilworth's theorem states that this is equal to finding maximum size subset that
	* pairwise are not connected
	* I.E. find all points that are top left or bottom right in respect to all other points
	* Sort by y, dp[i] = maximum len chain ended at point i
	* Note that the transition is exactly same as LIS
	* Thus we do LIS on x in NlogN using binary search or fenwick tree
*/
#include <bits/stdc++.h>
using namespace std;

pair<int, int> p[1000005];
int fwt[1000005];
void upd(int x, int v){
	for(; x < 1000005; x += x & -x)
		fwt[x] = max(fwt[x], v);
}
int que(int x){
	int res = 0;
	for(; x > 0; x -= x & -x)
		res = max(res, fwt[x]);
	return res;
}

int n, m, t[1000005], a[1000005];
vector<int> v;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;
	for(int i = 0; i < m; i ++) cin >> t[i];
	for(int i = 0; i < m; i ++) cin >> a[i];

	int mx = 0;
	for(int i = 0; i < m; i ++){
		p[i] = {t[i] + a[i], t[i] - a[i] - m};
		v.push_back(a[i] + m - t[i]);
	}

	sort(v.begin(), v.end());
	sort(p, p + m);

	for(int i = 0; i < m; i ++){
		int ps = lower_bound(v.begin(), v.end(), -p[i].second) - v.begin() + 1;
		int a = que(ps - 1) + 1;
		mx = max(mx, a);
		upd(ps, a);
	}

	cout << mx << endl;
	return 0;
}
#include "wiring.h"
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
const int N = 2e5 + 5;
const ll inf = 1e18 + 69;

int n, st[N], ed[N];
vector<pair<int, int> > v;
ll dp[N], pref[N];

ll min_total_length(vector<int> r, vector<int> b){
	n = r.size() + b.size();
	for(int i : r) v.push_back({i, 0});
	for(int i : b) v.push_back({i, 1});
	v.push_back({-1, -1});
	sort(v.begin(), v.end());

	st[1] = 1;
	for(int i = 2; i <= n; i ++)
		if(v[i].second == v[i - 1].second) st[i] = st[i - 1];
		else st[i] = i;

	ed[n] = n;
	for(int i = n - 1; i >= 1; i --)
		if(v[i].second == v[i + 1].second) ed[i] = ed[i + 1];
		else ed[i] = i;

	for(int i = 1; i <= n; i ++){
		dp[i] = inf;
		pref[i] = pref[i - 1] + v[i].first;

		if(ed[i] != n)
			dp[i] = min(dp[i], dp[i - 1] + v[ed[i] + 1].first - v[i].first);
		if(st[i] == 1) continue;
		if(st[i] == i){
			for(int j = i - 1; j >= st[i - 1]; j --)
				dp[i] = min(dp[i], dp[j - 1] + (i - j) * 1ll * v[i].first - (pref[i - 1] - pref[j - 1]));
		}
		dp[i] = min(dp[i], dp[i - 1] + v[i].first - v[st[i] - 1].first);
		if(st[i] - st[st[i] - 1] >= i - st[i] + 1)
			dp[i] = min(dp[i], dp[st[i] - (i - st[i] + 1) - 1] + pref[i] - pref[st[i] - 1] - (pref[st[i] - 1] - pref[st[i] - (i - st[i] + 1) - 1]));
	}

	return dp[n];
}
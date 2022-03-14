#include "tickets.h"
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

ll find_maximum(int k, vector<vector<int> > x){
	int n = x.size(), m = x[0].size();
	ll ans = 0ll;

	vector<vector<pair<ll, int> > > x2;
	x2.resize(n);
	for(int i = 0; i < n; i ++) for(int j = 0; j < m; j ++)
		x2[i].push_back({(ll)x[i][j], j});

	vector<pair<ll, pair<int, int> > > V;

	for(int i = 0; i < n; i ++){
		sort(x2[i].begin(), x2[i].end());
		for(int j = 0; j < k; j ++){
			V.push_back({x2[i][m - j - 1].first + x2[i][k - j - 1].first, {i, j}});	
			ans -= x2[i][j].first;
		}
	}

	sort(V.begin(), V.end(), [&](pair<ll, pair<int, int> > a, pair<ll, pair<int, int> > b){
		if(a.first == b.first) return a.second < b.second;
		return a.first > b.first;
	});

	vector<int> sum(n, 0);
	for(int i = 0; i < n * k / 2; i ++){
		ans += V[i].first;
		sum[V[i].second.first] = V[i].second.second + 1;
	}

	vector<vector<int> > res(n, vector<int>(m, -1));
	vector<int> fr(n, 0), bc(n, 0);
	for(int i = 0; i < k; i ++){
		vector<pair<int, int> > v;
		for(int j = 0; j < n; j ++) v.push_back({sum[j], j});
		sort(v.begin(), v.end());

		for(int j = 0; j < n / 2; j ++){
			res[v[j].second][x2[v[j].second][fr[v[j].second]].second] = i;
			fr[v[j].second] ++;
		}
		for(int j = n / 2; j < n; j ++){
			res[v[j].second][x2[v[j].second][m - bc[v[j].second] - 1].second] = i;
			bc[v[j].second] ++;
			sum[v[j].second] --;
		}
	}

	allocate_tickets(res);
	return ans;
}
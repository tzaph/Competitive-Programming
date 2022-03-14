#include "parks.h"
#include <bits/stdc++.h>
using namespace std;

int construct_roads(vector<int> x, vector<int> y){
	if(x.size() == 1){
		build({}, {}, {}, {});
		return 1;
	}
	
	int n = x.size();
	
	map<pair<int, int>, int> pt;
	set<pair<int, int> > bench;
	for(int i = 0; i < n; i ++){
		pt[{x[i], y[i]}] = i;

		for(int d = 0; d < 4; d ++)
			bench.insert({x[i] + (d >= 2 ? 1 : -1), y[i] + (d % 2 ? 1 : -1)});
	}

	int cc = 0;
	vector<bool> vis(n, 0);
	function <void(int, int)> dfs = [&](int nw, int bf){
		cc ++; vis[nw] = 1;
		int nwx = x[nw], nwy = y[nw];

		const int dx[] = {2, 0, -2, 0};
		const int dy[] = {0, 2, 0, -2};
		for(int d = 0; d < 4; d ++){
			int nxx = nwx + dx[d], nxy = nwy + dy[d];
			if(pt.count({nxx, nxy})){
				int nx = pt[{nxx, nxy}];
				if(bf != nx && !vis[nx])
					dfs(nx, nw);
			}
		}
	};

	dfs(0, 0);
	if(cc != n) return 0;

	vector<int> u, v, a, b;

	for(auto i : bench){
		int nwx = i.first, nwy = i.second;

		if((nwx + nwy) % 4 == 0){
			// vertical
			// force down
			if(pt.count({nwx - 1, nwy + 1}) && pt.count({nwx + 1, nwy + 1})){
				u.push_back(pt[{nwx - 1, nwy + 1}]);
				v.push_back(pt[{nwx + 1, nwy + 1}]);
				a.push_back(nwx);
				b.push_back(nwy);
			}
			// else try up
			else if(pt.count({nwx - 1, nwy - 1}) && pt.count({nwx + 1, nwy - 1})){
				u.push_back(pt[{nwx - 1, nwy - 1}]);
				v.push_back(pt[{nwx + 1, nwy - 1}]);
				a.push_back(nwx);
				b.push_back(nwy);
			}
		}else{
			// horizontal
			// force left
			if(pt.count({nwx - 1, nwy + 1}) && pt.count({nwx - 1, nwy - 1})){
				u.push_back(pt[{nwx - 1, nwy + 1}]);
				v.push_back(pt[{nwx - 1, nwy - 1}]);
				a.push_back(nwx);
				b.push_back(nwy);
			}
			// else try right
			else if(pt.count({nwx + 1, nwy + 1}) && pt.count({nwx + 1, nwy - 1})){
				u.push_back(pt[{nwx + 1, nwy + 1}]);
				v.push_back(pt[{nwx + 1, nwy - 1}]);
				a.push_back(nwx);
				b.push_back(nwy);
			}
		}
	}

	build(u, v, a, b);
	return 1;
}
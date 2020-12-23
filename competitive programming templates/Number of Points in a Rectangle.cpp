#include <vector>
#include <algorithm>
using namespace std;

struct tree_2d_t{
	vector<pair<int, int> > pts;
	vector<vector<int> > nodes;
	int base, n;

	tree_2d_t(const vector<pair<int, int> > & points){
		pts = points;
		sort(pts.begin(), pts.end());
		
		n = pts.size(); base = 1;
		while(base < n) base *= 2;

		nodes.resize(2 * base);
		for(int i = 0; i < n; i ++)
			nodes[base + i].push_back(pts[i].second);

		for(int i = base - 1; i >= 1; i --)
			merge(nodes[2 * i].begin(), nodes[2 * i].end(), nodes[2 * i + 1].begin(), nodes[2 * i + 1].end(), back_inserter(nodes[i]));
	}

	int que(int x, int yl, int yr){
		yl = lower_bound(nodes[x].begin(), nodes[x].end(), yl) - nodes[x].begin();
		yr = lower_bound(nodes[x].begin(), nodes[x].end(), yr + 1) - nodes[x].begin();
		return yr - yl;
	}

	int query(int xl, int xr, int yl, int yr){
		xl = lower_bound(pts.begin(), pts.end(), make_pair(xl, -1)) - pts.begin();
		xr = lower_bound(pts.begin(), pts.end(), make_pair(xr + 1, -1)) - pts.begin();

		int cnt = 0; xl += base; xr += base - 1;
		cnt += que(xl, yl, yr);
		if(xl != xr) cnt += que(xr, yl, yr);

		while(xl / 2 != xr / 2){
			if(~xl & 1) cnt += que(xl + 1, yl, yr);
			if(xr & 1) cnt += que(xr - 1, yl, yr);
			xl /= 2, xr /= 2;
		}

		return cnt;
	}
};
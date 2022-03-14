#include "prize.h"
#include <vector>
#include <set>
using namespace std;

set<int> s[200005];
int ans[200005];

int dnc(int cl, int cr){
	if(cl > cr) return -1;
	int md = (cl + cr) / 2;
	vector<int> gt = ask(md);
	ans[md] = gt[0];
	if(gt[0] + gt[1] == 0) return md;

	auto it = s[gt[0] + gt[1]].insert(md).first;
	if(it == s[gt[0] + gt[1]].begin() || ans[*prev(it)] != ans[md]){
		int rs = dnc(cl, md - 1);
		if(~rs) return rs;
	}
	if(it == --s[gt[0] + gt[1]].end() || ans[*next(it)] != ans[md]){
		int rs = dnc(md + 1, cr);
		if(~rs) return rs;
	}

	return -1;
}

int find_best(int n) {
	return dnc(0, n - 1);
}
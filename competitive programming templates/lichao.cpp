#include <iostream>
#include <set>
#include <limits.h>
#include <random>
using namespace std;
//Minimum CHT with indexing, take min index
//if no need index, remove every conditional with index
//if maximum, reverse comparator
#define ld long double
#define ll long long
const ld inf = 4e30 + 69;
const int lim = 2e5 + 5;
struct line{
	mutable ld m, c;
	mutable int id;
	ld operator()(ld x){
		return m * x + c;
	}
}lc[lim * 4];
//[cl, cr)
void insert(int nd, int cl, int cr, line seg){
	if(cr - cl == 1){
		if(seg(cl) < lc[nd](cl))
			lc[nd] = seg;
		return;
	}

	int md = (cl + cr) / 2;
	if(lc[nd].m < seg.m) swap(lc[nd], seg);
	if(lc[nd](md) > seg(md) || (lc[nd](md) == seg(md) && seg.id > lc[nd].id)){
		swap(lc[nd], seg);
		insert(nd * 2, cl, md, seg);
	}else insert(nd * 2 + 1, md, cr, seg);
}

pair<ld, int> query(int nd, int cl, int cr, ld x){
	if(lc[nd].id == 0) return {inf, 0};
	if(cr - cl == 1) return {lc[nd](x), lc[nd].id};

	int md = (cl + cr) / 2;
	pair<ld, int> rs;
	if(x < md) rs = query(nd * 2, cl, md, x);
	else rs = query(nd * 2 + 1, md, cr, x);

	if(rs.first == lc[nd](x)){
		if(lc[nd].id > rs.second)
			return {lc[nd](x), lc[nd].id};
		else return rs;
	}else if(rs.first < lc[nd](x)) return rs;
	return {lc[nd](x), lc[nd].id};
}
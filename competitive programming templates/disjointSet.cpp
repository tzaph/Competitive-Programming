#include <iostream>
#include <vector>
#include <array>
using namespace std;

int n, par[200005], off[200005];
void init(){
	for(int i = 1; i <= n; i ++){
		par[i] = -1;
		off[i] = 0;
	}
}
 
pair<int, int> gt(int x){
	int of = 0;
	while(par[x] >= 0){
		of ^= off[x];
		x = par[x];
	}
	return {x, of};
}
 
vector<array<int, 4> >md;
int uni(int _x, int _y){
	pair<int, int> x = gt(_x), y = gt(_y);
	if(x.first == y.first){
		if(x.second == y.second) return 0;
		md.push_back({-1, -1, -1, -1});
		return 1;
	}
 
	if(par[x.first] > par[y.first]) swap(x.first, y.first);
	md.push_back({x.first, y.first, par[x.first], par[y.first]});
	par[x.first] += par[y.first];
	par[y.first] = x.first;
	off[y.first] = x.second ^ y.second ^ 1;
	return 1;
}
 
void rollback(){
	auto a = md.back(); md.pop_back();
	if(a[0] != -1){
		par[a[0]] = a[2];
		par[a[1]] = a[3];
	}
}

void restore(int _sz){
	while(md.size() > _sz) rollback();
}
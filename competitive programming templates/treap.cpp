#include <iostream>
#include <set>
#include <limits.h>
#include <random>
using namespace std;

#define ll long long
struct node{
	node *l = 0, *r = 0;
	int val, pri, sz = 1;
	node(int val) : val(val), pri(rand()){}
	void recalc();
};
int cnt(node *x){
	return x ? x -> sz : 0;
}
void node::recalc(){
	sz = cnt(l) + cnt(r) + 1;
}

pair<node*, node*> split(node* n, int k){
	if(!n) return {};
	//if(n -> val >= k) for split by val = k
	if(cnt(n -> l) >= k){ 
		auto pa = split(n -> l, k);
		n -> l = pa.second;
		n -> recalc();
		return {pa.first, n};
	}else{
		auto pa = split(n -> r, k - cnt(n -> l) - 1);
		n -> r = pa.first;
		n -> recalc();
		return {n, pa.second};
	}
}

node* merge(node* l, node* r){
	if(!l) return r;
	if(!r) return l;

	if(l -> pri > r -> pri){
		l -> r = merge(l -> r, r);
		l -> recalc();
		return l;
	}else{
		r -> l = merge(l, r -> l);
		r -> recalc();
		return r;
	}
}

node* ins(node* rt, node* n, int ps){
	//put n in middle of rt
	auto pa = split(rt, ps);
	return merge(merge(pa.first, n), pa.second);
}
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define ll long long

struct node{
	int prior;
	int sz, val, mn;
	bool rev;
	node *cl, *cr;

	node(int v, int x = rng() % 1000000000) : prior(x), sz(1), val(v), 
		mn(v), rev(0), cl(NULL), cr(NULL) {}
};

typedef struct node* pnode;

int get_sz(pnode nd){
	return nd ? nd -> sz : 0;
}

void push(pnode nd){
	if(!nd) return;
	if(nd -> rev){
		nd -> rev ^= 1;
		swap(nd -> cl, nd -> cr);
		if(nd -> cl) nd -> cl -> rev ^= 1;
		if(nd -> cr) nd -> cr -> rev ^= 1;
	}
}

void pull(pnode nd){
	if(nd){
		nd -> sz = get_sz(nd -> cl) + 1 + get_sz(nd -> cr);
		nd -> mn = nd -> val;
		if(nd -> cl) nd -> mn = min(nd -> mn, nd -> cl -> mn);
		if(nd -> cr) nd -> mn = min(nd -> mn, nd -> cr -> mn);
	}
}

void merge(pnode &nd, pnode l, pnode r){
	push(l); push(r);
	if(!l || !r)
		nd = l ? l : r;
	else if(l -> prior > r -> prior)
		merge(l -> cr, l -> cr, r), nd = l;
	else
		merge(r -> cl, l, r -> cl), nd = r;
	pull(nd);
}

void split(pnode nd, pnode &l, pnode &r, int key, int add = 0){
	if(!nd) return void(l = r = NULL);
	push(nd);
	int cr = add + get_sz(nd -> cl);
	if(key <= cr)
		split(nd -> cl, l, nd -> cl, key, add), r = nd;
	else
		split(nd -> cr, nd -> cr, r, key, cr + 1), l = nd;
	pull(nd);
}

void reverse(pnode nd, int l, int r){
	pnode t1, t2, t3;
	split(nd, t1, t2, l);
	split(t2, t2, t3, r - l + 1);
	t2 -> rev ^= 1;
	merge(nd, t1, t2);
	merge(nd, nd, t3);
}

void erase(pnode &nd, int key, int add = 0){
	push(nd);
	int cr = add + get_sz(nd -> cl);
	if(key == cr){
		pnode tmp = nd;
		merge(nd, nd -> cl, nd -> cr);
		delete tmp;
	}else if(key < cr)
		erase(nd -> cl, key, add);
	else
		erase(nd -> cr, key, cr + 1);
	pull(nd);
}

int find(pnode nd, int val){
	push(nd);
	if(nd -> val == val) return get_sz(nd -> cl);
	if(nd -> cl && nd -> cl -> mn == val)
		return find(nd -> cl, val);
	else
		return get_sz(nd -> cl) + 1 + find(nd -> cr, val);
}
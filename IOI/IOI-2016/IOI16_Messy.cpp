#include "messy.h"
#include<bits/stdc++.h>
using namespace std;
#define init int cl=0, int cr=n-1
#define md (cl+cr)/2
#define lc cl, md
#define rc md+1, cr
int n, p[128];
void add(init){
	if(cl==cr) return;
	string str(n, '0');
	for(int i=cl; i<=cr; i++)
		str[i]='1';
	for(int i=md+1; i<=cr; i++){
		str[i]='0';
		add_element(str);
		str[i]='1';
	}
	add(lc); add(rc);
}
void check(vector<int>s, init){
	if(cl==cr){
		p[s[0]]=cl; return;
	}
	string str(n, '0');
	for(auto &i:s) str[i]='1';
	vector<int>l, r;
	for(auto &i:s){
		str[i]='0';
		if(check_element(str)) r.push_back(i);
		else l.push_back(i);
		str[i]='1';
	}
	check(l, lc); check(r, rc);
}
vector<int> restore_permutation(int _n, int w, int r){
	n=_n;
	add();
	compile_set();
	vector<int>v;
	for(int i=0; i<n; i++) v.push_back(i);
	check(v);
	vector<int>ans;
	for(int i=0; i<n; i++) ans.push_back(p[i]);
	return ans;
}
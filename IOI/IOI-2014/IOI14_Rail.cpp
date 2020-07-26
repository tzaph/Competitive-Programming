#include "rail.h"
#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> >v;
set<int>C, D;
void findLocation(int n, int first, int l[], int t[]){
	l[0]=first; t[0]=1; //block 0, C station
	for(int i=1; i<n; i++)
		v.push_back({getDistance(0, i), i});
	sort(v.begin(), v.end());
	l[v[0].second]=first+v[0].first;
	t[v[0].second]=2; //the first D station
	C.insert(l[0]);
	D.insert(l[v[0].second]);
	int L=0, R=v[0].second;
	for(int i=1; i<v.size(); i++){
		int idx=v[i].second;
		int lf=getDistance(idx, L);
		int rg=getDistance(idx, R);
		int lfcan=l[L]+lf, rgcan=l[R]-rg;
		bool isC;
		auto it1=--C.upper_bound(lfcan);
		if(rg==lfcan-*it1+l[R]-*it1){
			isC=false;
		}else{
			auto it2=D.upper_bound(rgcan);
			if(it2!=D.end() && lf==*it2-rgcan+*it2-l[L]){
				isC=true;
			}else{
				if(v[i].first==2*l[v[0].second]-l[0]-rgcan)
					isC=true;
				else isC=false;
			}
		}
		if(isC){
			l[idx]=rgcan;
			t[idx]=1;
			C.insert(l[idx]);
			if(l[L]>l[idx]) L=idx;
		}else{
			l[idx]=lfcan;
			t[idx]=2;
			D.insert(l[idx]);
			if(l[R]<l[idx]) R=idx;
		}
	}
}
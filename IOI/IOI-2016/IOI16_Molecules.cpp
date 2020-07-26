#include<bits/stdc++.h>
using namespace std;
vector<pair<int, int> >v;
vector<int> find_subset(int l, int u, vector<int>w){
	int n=w.size(); v.resize(n);
	for(int i=0; i<n; i++) v[i]={w[i], i};
	sort(v.begin(), v.end());
	int idx=0; long long sum=0ll;
	for(int i=0; i<n; i++){
		for(; idx<n && sum<l; idx++)
			sum+=v[idx].first;
		if(sum>=l && sum<=u){
			vector<int>res;
			for(int j=i; j<idx; j++) 
				res.push_back(v[j].second);
			sort(res.begin(), res.end());
			return res;
		}
		sum-=v[i].first;
	}
	return vector<int>();
}
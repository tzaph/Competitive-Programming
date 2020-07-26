#include"vision.h"
#include<bits/stdc++.h>
using namespace std;
vector<int>diagL[405], diagR[405], prefL, prefR, ans;
void reset(){
	for(int i=0; i<405; i++)
		diagL[i].clear(), diagR[i].clear();
	prefL.clear(); prefR.clear(); ans.clear();
}
int h, w;
int solve(int k){
	reset();
	for(int i=0; i<h; i++) for(int j=0; j<w; j++)
		diagL[i+j].push_back(i*w+j),
		diagR[i+(w-1-j)].push_back(i*w+j);
	for(int dst=k; dst<=h+w-2; dst++){
		prefL.push_back(add_or(diagL[dst-k]));
		ans.push_back(add_and({add_or(diagL[dst]), add_or(prefL)}));
		prefR.push_back(add_or(diagR[dst-k]));
		ans.push_back(add_and({add_or(diagR[dst]), add_or(prefR)}));
	}
	return add_or(ans);
}
void construct_network(int H, int W, int K){
	h=H; w=W;
	if(K==H+W-2) solve(K);
	else add_and({solve(K), add_not(solve(K+1))});
}
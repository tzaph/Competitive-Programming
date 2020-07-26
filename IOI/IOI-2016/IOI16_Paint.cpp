#include "paint.h"
#include<bits/stdc++.h>
using namespace std;
int vis[200005][105], dp[200005][105];
string ans, A;
vector<int>seg;
int suf[200005], isi[200005], empty[200005];
int n, k;
 
int f(int i, int lf){
	if(i>n) return 0;
	if(i==n) return lf==k;
	if(dp[i][lf]!=-1) return dp[i][lf];
	int rs=0;
	if(A[i]!='X') rs|=f(i+1, lf);
	if(lf<k && seg[lf]<=suf[i] && A[i+seg[lf]]!='X'){
		if(i+seg[lf]+1<=n)
			rs|=f(i+seg[lf]+1, lf+1);
		else rs|=f(i+seg[lf], lf+1);
	}
	return dp[i][lf]=rs;
}
void back(int i, int lf){
	if(i>=n || vis[i][lf]) return;
	vis[i][lf]=1;
	if(A[i]!='X' && f(i+1, lf)){
		empty[i]=1;
		back(i+1, lf);
	}
	if(lf<k && seg[lf]<=suf[i] && A[i+seg[lf]]!='X' && f(i+seg[lf]+(i+seg[lf]+1<=n), lf+1)){
		isi[i]++;
		isi[i+seg[lf]]--;
		empty[i+seg[lf]]=1;
		back(i+seg[lf]+1, lf+1);
	}
}
 
string solve_puzzle(string s, vector<int>c){
	A=s; seg=c;
	n=s.size(); k=c.size();
	for(int i=n-1; i>=0; i--)
		suf[i]=A[i]=='_'?0:1+suf[i+1];
	memset(dp, -1, sizeof(dp));
	f(0, 0); back(0, 0);
	int st=0;
	ans.resize(n);
	for(int i=0; i<n; i++){
		st+=isi[i];
		if(empty[i] && st>0) ans[i]='?';
		else if(empty[i]) ans[i]='_';
		else if(st>0) ans[i]='X';
	}
	return ans;
}
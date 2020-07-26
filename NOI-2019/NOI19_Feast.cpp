#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define gc getchar
#define pc putchar
int in(){
	char c=gc(); bool neg=false;
	for(; c<'0'||'9'<c; c=gc())
		if(c=='-') neg=true;
	int rs=c-'0'; c=gc();
	for(; '0'<=c && c<='9'; c=gc())
		rs=(rs<<1)+(rs<<3)+(c-'0');
	if(neg) rs=-rs;
	return rs;
}
void out(ll _n){
	ll N=_n, rev, count=0;
	rev=N;
	if(N==0) {pc('0'); return;}
	while((rev%10ll)==0) {count++; rev/=10;}
	rev=0;
	while(N!=0) {rev=(rev<<3ll)+(rev<<1ll)+N%10; N/=10;}
	while(rev!=0) {pc(rev%10ll+'0'); rev/=10;}
	while(count--) pc('0');
}
int n, k, val[300005];
pair<ll, int> dp[300005][2];
pair<ll, int> solve(ll x){
	for(int i=1; i<=n; i++){
		if(dp[i-1][0].first>dp[i-1][1].first-x)
			dp[i][0]=dp[i-1][0];
		else if(dp[i-1][0].first<dp[i-1][1].first-x)
			dp[i][0]={dp[i-1][1].first-x, dp[i-1][1].second+1};
		else if(dp[i-1][0].second<dp[i-1][1].second+1)
			dp[i][0]=dp[i-1][0];
		else dp[i][0]={dp[i-1][1].first-x, dp[i-1][1].second+1};
 
		if(dp[i-1][0].first>dp[i-1][1].first)
			dp[i][1]=dp[i-1][0];
		else if(dp[i-1][0].first<dp[i-1][1].first)
			dp[i][1]=dp[i-1][1];
		else if(dp[i-1][0].second<dp[i-1][1].second)
			dp[i][1]=dp[i-1][0];
		else dp[i][1]=dp[i-1][1];
		dp[i][1]={dp[i][1].first+val[i], dp[i][1].second};
	}
	pair<ll, int> ans;
	if(dp[n][0].first>dp[n][1].first-x)
		ans=dp[n][0];
	else if(dp[n][0].first<dp[n][1].first-x)
		ans={dp[n][1].first-x, dp[n][1].second+1};
	else if(dp[n][0].second<dp[n][1].second+1)
		ans=dp[n][0];
	else ans={dp[n][1].first-x, dp[n][1].second+1};
	return ans;
}
int main(){
	n=in(), k=in();
	for(int i=1; i<=n; i++) val[i]=in();
	ll l=0, r=3e14, md;
	while(l<=r){
		md=(l+r)/2;
//		cout<<md<<" "<<solve(md).first<<" "<<solve(md).second<<endl;
		if(solve(md).second>k) l=md+1;
		else r=md-1;
	}
//	cout<<l<<endl;
	ll ans=solve(l).first+l*(ll)k;
	out(ans); pc('\n'); return 0;
}
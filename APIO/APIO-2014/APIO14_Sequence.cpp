#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n, k, a[100005], cht[100005], bt[100005][205];
ll pref[100005], dp[100005], dplast[100005];
long double slp(int id1, int id2){
	if(pref[id1]==pref[id2]) return -1e18;
	return (long double)((dplast[id1]-pref[id1]*pref[id1])-(dplast[id2]-pref[id2]*pref[id2]))/(long double)(pref[id2]-pref[id1]);
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i=1; i<=n; i++){
		scanf("%d", &a[i]);
		pref[i]=pref[i-1]+a[i];
	}
	for(int j=1; j<=k; j++){
		int lf=1, rg=0;
		cht[++rg]=0;
		for(int i=1; i<=n; i++){
			while(lf<rg && slp(cht[lf], cht[lf+1])<=pref[i]) lf++;
			dp[i]=dplast[cht[lf]]+pref[cht[lf]]*(pref[i]-pref[cht[lf]]);
			bt[i][j]=cht[lf];
			while(lf<rg && slp(cht[rg-1], cht[rg])>=slp(cht[rg], i)) rg--;
			cht[++rg]=i;
		}
		for(int i=1; i<=n; i++)
			dplast[i]=dp[i];
	}
	printf("%lld\n", dp[n]);
	for(int x=n, i=k; i>=1; i--){
		x=bt[x][i];
		printf("%d%c", x, (i==1?'\n':' '));
	}
	return 0;
}
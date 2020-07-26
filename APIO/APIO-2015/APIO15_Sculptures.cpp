#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int inf = 1e9;
ll v[2005];
int dp[2005], n, l, r;

bool check(ll msk){
	for(int i = 0; i <= n; i++)
		dp[i] = inf;
	dp[0] = 0;

	for(int i = 0; i < n; i ++) if(dp[i] < inf){
		ll crsm = 0ll;
		for(int j = i; j < n; j ++){
			crsm += v[j];
			if((crsm & msk) == 0)
				dp[j + 1] = min(dp[j + 1], dp[i] + 1);
		}
	}

	return dp[n] <= r;
}

bool dp2[105][105];
bool check2(ll msk){
	for(int i = 0; i <= n; i ++) for(int j = 0; j <= n; j ++)
		dp2[i][j] = false;
	dp2[0][0] = true;
	for(int j = 0; j <= r; j ++) for(int i = 0; i < n; i ++){
		if(dp2[i][j]){
			ll crsm = 0ll;
			for(int k = i; k < n; k ++){
				crsm += v[k];
				if((crsm & msk) == 0)
					dp2[k + 1][j + 1] = 1;
			}
		}
	}
	for(int i = l; i <= r; i ++)
		if(dp2[n][i]) return true;
	return false;
}

int main(){
	cin >> n >> l >> r;
	for(int i = 0; i < n; i ++)
		cin >> v[i];
	if(l == 1){
		ll ans = 0ll;
		for(int i = 60; i >= 0; i --)
			if(check(ans | (1ll << i)))
				ans |= (1ll << i);
		cout << (1ll << 61) - 1ll - ans << endl;
	}else{
		ll ans = 0ll;
		for(int i = 60; i >= 0; i --)
			if(check2(ans | (1ll << i)))
				ans |= (1ll << i);
		cout << (1ll << 61) - 1ll - ans << endl;
	}
	return 0;
}
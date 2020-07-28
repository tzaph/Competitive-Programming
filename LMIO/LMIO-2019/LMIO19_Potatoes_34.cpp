/*
    * LMIO 2019 Potatoes and Fertilizers (Subtask 1 and 2, 34 Points)
    * For subtask 1, just count every distance by summing absolute values of pref_a - pref_b
    * For subtask 2, do the same but both ways, prefix and suffix
    * Iterate every index, take left prefix + right suffix, take minimum value
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#define ll long long
ll arr[500005], pref[500005], dp[500005][2];
int n, a, b;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a >> b;
		arr[i] = a - b;
		pref[i] = pref[i - 1] + (ll)arr[i];
	}

	ll ans = 1000000000000000000ll;

	for(int i = 1; i <= n; i ++)
		dp[i][0] = dp[i - 1][0] + abs(pref[i]);
	for(int i = n; i >= 1; i --)
		dp[i][1] = dp[i + 1][1] + abs(pref[i] - 1);

	if(pref[n] == 0){
		cout << dp[n][0] << endl;
		return 0;
	}

	for(int i = 1; i <= n; i ++)
		ans = min(ans, dp[i - 1][0] + dp[i][1]);
	cout << ans << endl;
	return 0;
}

/*
	* NOI 2020 B Discharging
	* Take prefix maximum
	* Smaller elements will follow the larger elements upfront
	* DP N^2 -> DP[x] = min(DP[i - 1] + T[x](N - i + 1)) for all i <= x
	* Rearrange the formula to DP[x] = T[x](N + 1) + min(-i * T[x] + DP[i - 1])
	* We can use DP CHT with gradients -i and constants DP[i - 1]
	* Then find the minimum value for T[x]
	* The gradients we queried are sorted, thus DP CHT can be done in O(N)
*/
#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define ll long long
typedef tuple<ld, ll, ll> tp;

bool cmp(tp a, tp b, ll m, ll c){
	ld m1, c1, m2, c2, tmp;
	tie(tmp, m1, c1) = a;
	tie(tmp, m2, c2) = b;
	return (c - c2) * (ld)1.0 * (m1 - m) < (c - c1) * (ld)1.0 * (m2 - m);
}

ld intersec(tp a, tp b){
	ld m1, c1, m2, c2, tmp;
	tie(tmp, m1, c1) = a;
	tie(tmp, m2, c2) = b;
	return (ld)(c1 - c2)/(ld)(m2 - m1);
}

ll solve(int n, vector<ll> t){
	deque<tp> ch;
	ll cr_mx = 0ll, cr_dp = 0ll;
	for(int i = 1; i <= n; i ++){
		ll cr = t[i];
		if(cr >= cr_mx){
			ll m = 1 - i, c = cr_dp;
			while(ch.size() >= 2 && cmp(ch[ch.size() - 2], ch.back(), m, c))
				ch.pop_back();

			tp line = make_tuple(2e9, m, c);
			if(i != 1) get<0>(ch.back()) = intersec(ch.back(), line);

			ch.push_back(line);
			cr_mx = cr;

			while(get<0>(ch.front()) < (ld)cr_mx)
				ch.pop_front();

			ld tmp;
			tie(tmp, m, c) = ch.front();
			cr_dp = n * cr_mx + m * cr_mx + c;
		}
	}
	return cr_dp;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<ll> t(n + 1);
	for(int i = 1; i <= n; i ++) cin >> t[i];
	cout << solve(n, t) << endl;
	return 0;
}
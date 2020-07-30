#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 69;
int t, n, k1, k2;
int dp[65][65][65 * 65 / 2 + 5];
tuple<int, int, int> bt[65][65][65 * 65 / 2 + 5];
int arr[305][305], ans[305][305];
int cc[65][65], cc_ans[65][65];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> t >> n >> k1 >> k2;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			cin >> arr[i][j];

	int comp = (n + 59) / 60;
	int nn = n / comp;
	for(int i = 1; i <= n; i ++) for(int j = 1; j <= n; j ++)
		cc[(i + comp - 1) / comp][(j + comp - 1) / comp] += arr[i][j];
	for(int i = 1; i <= nn; i ++) for(int j = 1; j <= nn; j ++)
		cc[i][j] += cc[i][j - 1];

	for(int i = 0; i < 65; i ++) for(int j = 0; j < 65; j ++)
		for(int k = 0; k < 65 * 65 / 2 + 5; k ++){
			dp[i][j][k] = inf;
			bt[i][j][k] = make_tuple(-1, -1, -1);
		}

	dp[nn + 1][0][0] = 0;
	for(int i = nn + 1; i >= 1; i --) for(int j = 0; j <= nn; j ++)
		for(int k = 0; k <= nn * nn / 2; k ++) if(dp[i][j][k] != inf){
			if(k + j <= nn * nn / 2){
				if(dp[i - 1][j][k + j] > dp[i][j][k] + cc[i - 1][j]){
					dp[i - 1][j][k + j] = dp[i][j][k] + cc[i - 1][j];
					bt[i - 1][j][k + j] = make_tuple(i, j, k);
				}
			}
			if(dp[i][j + 1][k] > dp[i][j][k]){
				dp[i][j + 1][k] = dp[i][j][k];
				bt[i][j + 1][k] = make_tuple(i, j, k);
			}
		}

	int i = 1, j = nn, k = nn * nn / 2;
	while(i != -1){
		if(get<0>(bt[i][j][k]) == i + 1){
			for(int l = 1; l <= nn; l ++)
				cc_ans[i][l] = (l > j);
		}
		tie(i, j, k) = bt[i][j][k];
	}

	for(int i = 1; i <= nn; i ++) for(int j = 1; j <= nn; j ++)
		for(int ii = 1; ii <= comp; ii ++) for(int jj = 1; jj <= comp; jj ++)
			ans[(i - 1) * comp + ii][(j - 1) * comp + jj] = cc_ans[i][j];

	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			cout << ans[i][j];
			if(j < n) cout << " ";
		}
		cout << endl;
	}

	return 0;
}

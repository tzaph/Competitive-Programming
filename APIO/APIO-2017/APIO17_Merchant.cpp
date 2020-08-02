#include <iostream>
using namespace std;

#define ll long long
int n, m, k;
const ll inf = 1e18 + 69;
ll dist[105][105], profit[105][105];
ll res[105][105];
ll buy[105][1005], sell[105][1005];

bool check(ll penalty){
	for(int u = 1; u <= n; u ++) for(int v = 1; v <= n; v ++){
		if(dist[u][v] == inf) res[u][v] = -inf;
		else res[u][v] = max((ll)profit[u][v] - dist[u][v] * 1ll * penalty, -inf);
	}
	for(int u = 1; u <= n; u ++) res[u][u] = -inf;
	ll ans = -inf;
	for(int z = 1; z <= n; z ++){
		for(int x = 1; x <= n; x ++) for(int y = 1; y <= n; y ++){
			res[x][y] = max(res[x][z] + res[z][y], res[x][y]);
			ans = max(ans, res[x][x]);
		}
	}
	if(ans >= 0ll) return true;
	return false;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++) for(int j = 1; j <= n; j ++){
		if(i != j) dist[i][j] = inf;
		else dist[i][j] = 0;
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= k; j ++)
			cin >> buy[i][j] >> sell[i][j];
	for(int u, v, wt, i = 1; i <= m; i ++){
		cin >> u >> v >> wt;
		dist[u][v] = wt;
	}

	for(int z = 1; z <= n; z ++)
		for(int x = 1; x <= n; x ++)
			for(int y = 1; y <= n; y ++)
				dist[x][y] = min(dist[x][y], dist[x][z] + dist[z][y]);

	for(int x = 1; x <= n; x ++)
		for(int y = 1; y <= n; y ++){
			profit[x][y] = 0ll;
			if(x != y)
				for(int z = 1; z <= k; z ++){
					if(buy[x][z] == -1 || sell[y][z] == -1) continue;
					profit[x][y] = max(profit[x][y], sell[y][z] - buy[x][z]);
				}
		}

	ll lf = 1, rg = 1000000007ll, res = 0ll;
	for(int md; lf <= rg;){
		md = (lf + rg) / 2;
		if(check(md)){
			res = md;
			lf = md + 1;
		}else{
			rg = md - 1;
		}
	}

	cout << res << endl;
	return 0;
}

/*
	* LMIO 2019 Tax Evasion
	* Main Idea : Euler tour, binary search the answer
	* If there's a coin at depth d, it can only climb to
	* floor((d - 1) / 2), as Just will get caught afterwards
	* So we can build an euler tour, coin X can only stay at
	* a range L to R
	* Binary search the answer: if a is a candidate answer, 
	* all coins should have depth at least a - 1
	* Check if >= a possible using greedy
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
int n, m, timer;
int par[18][200005], depth[200005], lf[200005], rg[200005];
bool is_coin[200005];
vector<int> adj[200005], que[200005], order;
 
void euler_tour(int nw){
	order.push_back(nw);
	lf[nw] = timer ++;
	for(int nx : adj[nw])
		euler_tour(nx);
	rg[nw] = timer;
}
 
int anc(int nw, int dp){
	for(int i = 17; i >= 0; i --)
		if(dp & (1 << i)) nw = par[i][nw];
	return nw;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
 
	cin >> n >> m;
	for(int p, i = 2; i <= n; i ++){
		cin >> p;
		par[0][i] = p;
		depth[i] = depth[p] + 1;
		adj[p].push_back(i);
	}
 
	for(int i = 1; i < 18; i ++) for(int j = 1; j <= n; j ++)
		par[i][j] = par[i - 1][par[i - 1][j]];
 
	for(int p, i = 0; i < m; i ++){
		cin >> p;
		is_coin[p] = true;
	}
 
	euler_tour(1);
	
	for(int i = 1; i <= n; i ++) if(is_coin[i]){
		int up = anc(i, (depth[i] - 1) / 2);
		que[lf[up]].push_back(rg[up]);
	}
 
	int res = 0;
	for(int l = 0, r = n, md; l <= r; ){
		md = (l + r) / 2;
		priority_queue<int, vector<int>, greater<int> > pq;
		bool can = true;
 
		for(int i = 0; i < n && can; i ++){
			for(int j : que[i]) pq.push(j);
			if(depth[order[i]] >= md && !pq.empty()){
				int nw = pq.top(); pq.pop();
				if(nw <= i) can = false;
			}
		}
 
		if(!pq.empty()) can = false;
 
		if(can){
			res = md; l = md + 1;
		}else{
			r = md - 1;
		}
	}
 
	cout << res + 1 << endl;
	return 0;
}

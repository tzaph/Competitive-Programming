#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct slop{
	ll a, b;
	priority_queue<ll>pq;
	slop& operator+=(slop& x){
		a+=x.a; b+=x.b;
		if(x.pq.size()>pq.size())
			swap(pq, x.pq);
		for(;!x.pq.empty();x.pq.pop())
			pq.push(x.pq.top());
		return *this;
	}
}f[300005];
ll cst[300005];
vector<int>adj[300005];
void dfs(int nw){
	if(adj[nw].size()==0){ //leaf
		f[nw].a=1; f[nw].b=-cst[nw];
		f[nw].pq.push(cst[nw]);
		f[nw].pq.push(cst[nw]);
		return;
	}
	for(int nx:adj[nw]){
		dfs(nx);
		f[nw]+=f[nx];
	}
	//>1 useless, reduce
	for(;f[nw].a>1;){ 
		f[nw].a-=1;
		f[nw].b+=f[nw].pq.top();
		f[nw].pq.pop();
	}
	//shift 0 and 1
	ll fi=f[nw].pq.top()+cst[nw]; f[nw].pq.pop();
	ll sc=f[nw].pq.top()+cst[nw]; f[nw].pq.pop();
	f[nw].pq.push(fi); f[nw].pq.push(sc);
	//after shift, reduce b
	f[nw].b-=cst[nw];
}
int main(){
	int n, m; scanf("%d%d", &n, &m);
	for(int i=2, bf; i<=n+m; i++){
		scanf("%d%lld", &bf, &cst[i]);
		adj[bf].push_back(i);
	}
	dfs(1);
	printf("%lld\n", f[1].a*f[1].pq.top()+f[1].b);
	return 0;
}
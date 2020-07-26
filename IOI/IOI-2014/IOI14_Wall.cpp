#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=1e18;
ll stmax[8000888], stmin[8000888], h[8000888];
void down(ll idx, ll mn, ll mx){
	stmin[idx]=min(stmin[idx], mn);
	stmax[idx]=min(stmax[idx], mn);
	stmax[idx]=max(stmax[idx], mx);
}
void upd(ll cl, ll cr, ll lf, ll rg, ll nd, ll valmn, ll valmx){
	if(cl==cr) h[cl]=stmax[nd];
	else if(stmin[nd]!=inf || stmax[nd]!=0){
		down(nd*2, stmin[nd], stmax[nd]);
		down(nd*2+1, stmin[nd], stmax[nd]);
		stmin[nd]=inf;
		stmax[nd]=0;
	}
	if(cr<lf || rg<cl) return;
	else if(lf<=cl && cr<=rg)
		down(nd, valmn, valmx);
	else{
		upd(cl, (cl+cr)/2, lf, rg, nd*2, valmn, valmx);
		upd((cl+cr)/2+1, cr, lf, rg, nd*2+1, valmn, valmx);
	}
}
void buildWall(int n, int k, int op[], int lf[], int rg[], int H[], int fh[]){
	for(int i=1; i<=4*n; i++) stmin[i]=inf;
	for(int i=0; i<k; i++){
		if(op[i]==1)
			upd(0, n-1, lf[i], rg[i], 1, inf, H[i]);
		else
			upd(0, n-1, lf[i], rg[i], 1, H[i], 0);
	}
	for(int i=0; i<n; i++)
		upd(0, n-1, i, i, 1, inf, 0);
	for(int i=0; i<n; i++)
		fh[i]=h[i];
}
#include<bits/stdc++.h>
using namespace std;
#define ll long long
priority_queue<ll>lf;
priority_queue<ll, vector<ll>, greater<ll> >rg;
ll ans=0ll, h;
int n;
int main(){
	scanf("%d%lld", &n, &h);
	for(int i=0; i<n; i++){
		ll x;
		scanf("%lld", &x);
		if(i==0){
			lf.push(x); rg.push(x);
			continue;
		}
		ll shift=i*1ll*h;
		ll lfb=lf.top()-shift, rgb=rg.top()+shift;
		if(x<lfb){
			lf.push(x+shift); lf.push(x+shift);
			lf.pop();
			rg.push(lfb-shift);
			ans+=lfb-x;
		}else if(x>rgb){
			rg.push(x-shift); rg.push(x-shift);
			rg.pop();
			lf.push(rgb+shift);
			ans+=x-rgb;
		}else{
			lf.push(x+shift); rg.push(x-shift);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
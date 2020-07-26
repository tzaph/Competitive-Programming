#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18+69;
vector<pair<int, int> >seg;
int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n, a, b;
	cin>>n>>a>>b;
	int gcd=__gcd(a, b+1);
	int t;
	if(a/gcd>inf/b) t=inf; //a*b/gcd>inf
	else t=(a/gcd)*b;
	for(int i=0; i<n; i++){
		int l, r; cin>>l>>r;
		if(r-l+1>=t) seg.push_back({0, t-1});
		else{
			l%=t; r%=t;
			if(l<=r) seg.push_back({l, r});
			else{
				seg.push_back({l, t-1});
				seg.push_back({0, r});
			}
		}
	}
	sort(seg.begin(), seg.end());
	int ans=0;
	for(int i=0; i<(int)seg.size(); i++){
		int l=seg[i].first, r=seg[i].second;
		int nxt=i;
		while(nxt+1<seg.size()&&seg[nxt+1].first<=r){
			r=max(r, seg[nxt+1].second); nxt++;
		}
		ans+=r-l+1; i=nxt;
	}
	cout<<ans<<endl; return 0;
}
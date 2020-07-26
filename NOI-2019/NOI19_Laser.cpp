#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc putchar
int in(){
	char c=gc();
	for(; c<'0'||'9'<c; c=gc());
	int rs=c-'0'; c=gc();
	for(; '0'<=c && c<='9'; c=gc())
		rs=(rs<<1)+(rs<<3)+(c-'0');
	return rs;
}
void out(int _n){
	int N=_n, rev, count=0;
	rev=N;
	if(N==0) {pc('0'); return;}
	while((rev%10)==0) {count++; rev/=10;}
	rev=0;
	while(N!=0) {rev=(rev<<3)+(rev<<1)+N%10; N/=10;}
	while(rev!=0) {pc(rev%10+'0'); rev/=10;}
	while(count--) pc('0');
}
vector<pair<int, int> >ansv;
vector<int>v;
int len, n;
int main(){
	len=in(), n=in();
	for(int tc=0; tc<n; tc++){
		int x=in();
		v.resize(x+1); v[0]=0;
		for(int i=1; i<=x; i++)
			v[i]=in()+v[i-1];
		for(int i=1; i<=x; i++){
			int lf=len-(v[x]-v[i-1])+1, rg=v[i];
			if(lf<=rg) ansv.emplace_back(lf, rg);
		}
	}
	sort(ansv.begin(), ansv.end());
	if(ansv.size()==0){pc('0'); pc('\n'); return 0;}
	int lf=ansv[0].first, rg=ansv[0].second, ans=0;
	for(int i=1; i<ansv.size(); i++){
		int ln=ansv[i].first, rn=ansv[i].second;
		if(rg+1<ln){
			ans+=rg-lf+1;
			lf=ln; rg=rn;
		}else rg=max(rg, rn);
	}
	ans+=rg-lf+1;
	out(ans); pc('\n'); return 0;
}
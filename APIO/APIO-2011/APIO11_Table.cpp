#include<bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define pc putchar_unlocked
int get_i(){
	char c=gc(); bool neg=false;
	for(; c<'0'||'9'<c; c=gc())
		if(c=='-') neg=true;
	int rs=c-'0'; c=gc();
	for(; '0'<=c && c<='9'; c=gc())
		rs=(rs<<1)+(rs<<3)+(c-'0');
	if(neg) rs=-rs;
	return rs;
}
void print_i(int _n){
	bool neg=false; if(_n<0) {neg=true; _n=-_n;}
	if(neg) pc('-');
	int N=_n, rev, count=0;
	rev=N;
	if(N==0) {pc('0'); return;}
	while((rev%10)==0) {count++; rev/=10;}
	rev=0;
	while(N!=0) {rev=(rev<<3)+(rev<<1)+N%10; N/=10;}
	while(rev!=0) {pc(rev%10+'0'); rev/=10;}
	while(count--) pc('0');
}
const int mod=1e9, mxn=1e5+5;
int n, m, k, x[mxn], y[mxn], par[mxn*4];
int f(int x){return par[x]==x?x:par[x]=f(par[x]);}
int main(){
	n=get_i(), m=get_i(), k=get_i();
	for(int i=1; i<=n+m+n+m; i++) par[i]=i;
	for(int i=0; i<k; i++){
		int col; x[i]=get_i(), y[i]=get_i(), col=get_i();
		col^=((x[i]&1)&&(y[i]&1));
		int a=x[i], b=n+y[i], c=n+m+x[i], d=n+n+m+y[i];
		if(col){par[f(a)]=f(b); par[f(c)]=f(d);}
		else{par[f(a)]=f(d); par[f(c)]=f(b);}
	}
	int cnt=0;
	for(int i=1; i<=n+m; i++){
		if(f(i)==f(n+m+i)){
			cout<<0<<endl; return 0;
		}
		if(par[i]==i) cnt++;
	}
	int ans=1;
	for(int i=0; i<cnt-1; i++) ans=(2*ans)%mod;
	print_i(ans); pc('\n'); return 0;
}
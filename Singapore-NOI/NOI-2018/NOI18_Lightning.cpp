#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define gc getchar_unlocked
#define pc putchar_unlocked
int in(){
	char c=gc(); bool neg=false;
	for(; c<'0'||'9'<c; c=gc())
		if(c=='-') neg=true;
	int rs=c-'0'; c=gc();
	for(; '0'<=c && c<='9'; c=gc())
		rs=(rs<<1)+(rs<<3)+(c-'0');
	if(neg) rs=-rs;
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
int pref[10000005], suff[10000005];
int n, x, y;
int main(){
	n=in();
	for(int i=0; i<n; i++){
		x=in(), y=in();
		pref[i]=x+y;
		suff[i]=y-x;
		if(i>0) pref[i]=max(pref[i], pref[i-1]);
	}
	int ans=0;
	for(int i=n-1; i>=0; i--){
		if((i==0||pref[i]>pref[i-1])
		 &&(i==n-1||suff[i]>suff[i+1]))
			ans++;
		if(i<n-1) suff[i]=max(suff[i], suff[i+1]);
	}
	out(ans); pc('\n'); return 0;
}
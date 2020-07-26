#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define gc getchar
#define pc putchar
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
char get_c(){
	char c=gc();
	for(; c!='.' && c!='M' && c!='S'; c=gc());
	return c;
}
int r, c, d, k;
vector<pair<int, int> >mush;
vector<vector<int> >pref;
int main(){
	r=in(), c=in(), d=in(), k=in();
	pref.resize(r+1, vector<int>(c+1));
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			char c=get_c();
			if(c=='.') pref[i][j]=0;
			if(c=='M'){
				pref[i][j]=0; mush.push_back({i, j});
			}
			if(c=='S') pref[i][j]=1;
		}
	}
	for(int i=1; i<=r; i++)
		for(int j=1; j<=c; j++)
			pref[i][j]+=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1];
	int ans=0;
	for(pair<int, int> pt:mush){
		int brx=pt.first+d, bry=pt.second+d;
		int tlx=pt.first-d, tly=pt.second-d;
		if(brx>r) brx=r; if(bry>c) bry=c;
		if(tlx<1) tlx=1; if(tly<1) tly=1;
		int cnt=pref[brx][bry]-pref[brx][tly-1]-pref[tlx-1][bry]+pref[tlx-1][tly-1];
		if(cnt>=k) ans++;
	}
	out(ans); pc('\n'); return 0;
}
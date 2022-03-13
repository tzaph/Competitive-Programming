#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;

#define gc getchar//_unlocked //can't for window server
#define pc putchar//_unlocked //can't for window server
#define ll long long
#define ld long double
#define endl pc('\n')
void read(int &x){
	char c = gc(); bool neg = false;
	for(; c < '0'||'9' < c; c = gc())
		if(c == '-') neg=true;
	x = c - '0'; c = gc();
	for(; '0' <= c && c <= '9'; c = gc())
		x = (x << 1) + (x << 3) + (c - '0');
	if(neg) x = -x;
}
void read(string &s){
	s = "";
	for(char c = gc(); c != ' ' && c != '\n' && c != EOF; c = gc())
		s += c;
}
void read(ld &s){
	string x; read(x);
	ll w = 0; int tp = -1;
	for(int i = 0; i < x.size(); i ++){
		if(x[i] != '.')
			w = w * 10 + (x[i] - '0');
		else tp = i;
	}
	s = w;
	if(tp != -1) s /= pow(10.0, x.size() - tp - 1);
}
void pri(ll _n){
	ll N = _n, rev, count = 0;
	bool neg = false;
	if(N < 0){
		N = -N; neg = true;
	}
	rev = N;
	if(N == 0) {pc('0'); return;}
	if(neg) pc('-');
	while(rev % 10 == 0) {count ++; rev /= 10;}
	rev = 0;
	while(N != 0) {rev = (rev << 3) + (rev << 1) + N % 10; N /= 10;}
	while(rev != 0) {pc(rev % 10 + '0'); rev /= 10;}
	while(count --) pc('0');
}
void pri(string s){
	for(int i = 0; i < s.size(); i ++)
		pc(s[i]);
}
void pri(ld x){
	printf("%.12Lf", x);
}
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <string.h>
#include <set>
#include <math.h>
#include <numeric>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <queue>
#include <deque>
#include <random>
#include <chrono>
#include <limits.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long
#define ld double
#define endl "\n"
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> OST_multiset;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
const int inf = 1e9 + 69;
const ll infll = inf * 1ll * inf;
const ld pi = 3.14159265358979323L;
const ld eps = 1e-10;

void setIn(string s){freopen(s.c_str(), "r", stdin);}
void setOut(string s){freopen(s.c_str(), "w", stdout);}
void unsyncIO(){cin.tie(0) -> sync_with_stdio(0);}
void setIO(string s = ""){
    unsyncIO();
    if(s.size()){
        setIn(s + ".in");
        setOut(s + ".out");
    }
}

#define gc getchar//_unlocked //can't for window server
#define pc putchar//_unlocked //can't for window server
ll inp(){
	char c = gc(); bool neg = false;
	for(; c < '0'||'9' < c; c = gc())
		if(c == '-') neg=true;
	ll rs = c - '0'; c = gc();
	for(; '0' <= c && c <= '9'; c = gc())
		rs = (rs << 1) + (rs << 3) + (c - '0');
	if(neg) rs = -rs;
	return rs;
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

const ll mod = 1e9 + 7;
const int MX = 5005;

int main(){
	setIO();

	return 0;
}
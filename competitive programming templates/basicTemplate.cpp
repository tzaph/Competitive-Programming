#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> OST_multiset;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
#define ll long long
#define ld long double
#define endl "\n"
const int MX = 100005;
const int BLOCK = 205;
const int inf = 1000000069;
const ll inf_ll = 8000000000000000069ll;
const ll mod = 1e9 + 7;
const ll inv2 = (mod + 1) / 2;
const int dxh[] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dyh[] = {2, -2, 2, -2, 1, -1, 1, -1}; // horse
const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0}; // adj
const int dz[] = {0, 0, 0, 0, 1, -1}; // 3d
const int dxd[] = {1, 1, 1, 0, -1, -1, -1, 0};
const int dyd[] = {1, 0, -1, -1, -1, 0, 1, 1}; // diag

bool untied = 0;
void setIn(string s){freopen(s.c_str(), "r", stdin);}
void setOut(string s){freopen(s.c_str(), "w", stdout);}
void unsyncIO(){cin.tie(0) -> sync_with_stdio(0);}
void setIO(string s = ""){
    if(!untied) unsyncIO(), untied = 1;
    if(s.size()){
        setIn(s + ".in");
        setOut(s + ".out");
    }
}

int main(){
	setIO();

	return 0;
}
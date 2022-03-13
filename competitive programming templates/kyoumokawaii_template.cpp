#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define kyou using
#define mo namespace
#define kawaii std
#define chisai chrono
#define dekai __gnu_pbds;

kyou mo kawaii;
kyou mo chisai;
kyou mo dekai;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define endl "\n"
#define ohamachi cin.tie(0) -> sync_with_stdio(0)
#define otsumachi exit(0)
#define ll long long
#define ld double
const int MX = 100005;
const int LG = 30;
const int BLOCK = 330;
const int inf = 1e9 + 69;
const ll mod = 1e9 + 7;
const ll inv2 = (mod + 1) / 2ll;
const ll infll = 4e18 + 6969;
const short dx[] = {0, 1, 0, -1};
const short dy[] = {1, 0, -1, 0};
const ld eps = 1e-6;

class timer: high_resolution_clock{
	const time_point start_time;
public:
	timer():start_time(now()){}
	rep elapsed_time() const{ 
		return duration_cast<milliseconds>(now() - start_time).count(); 
 	}
};

int main(){
	ohamachi;

	
	otsumachi;
}
#include <bits/stdc++.h>
#include <bits/extc++.h> //cant remember ext headers lol
using namespace std;

#define ll long long
const int randd = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash{
	const uint64_t C = (ll)(4e18 * acos(0)) | 71;
	ll operator()(ll x) const{
		return __builtin_bswap64((x ^ randd) * C);
	}
};

__gnu_pbds::gp_hash_table<ll, int, chash> mp({}, {}, {}, {}, {1 << 16});

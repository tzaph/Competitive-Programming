#include "boxes.h"
#include <algorithm>
using namespace std;

long long tmp = 0ll, pref[10000005], suff[10000005];

long long delivery(int N, int K, int L, int p[]) {
	for(int i = 1; i <= N; i ++){
		pref[i] = min(p[i - 1] << 1, L);
		if(i > K) pref[i] += pref[i - K];
	}

	for(int i = N - 1; i >= 0; i --){
		suff[i] = min((L - p[i]) << 1, L);
		if(N - i > K) suff[i] += suff[i + K];
	}

	long long ans = pref[N];
	for(int i = 0; i < N; i ++)
		ans = min(ans, pref[i] + suff[i]);

    return ans;
}
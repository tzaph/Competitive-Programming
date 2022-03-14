#include <vector>
#include <set>
#include "advisor.h"
using namespace std;

void ComputeAdvice(int *C, int N, int K, int M) {
	vector<int> last_id(N + K), last_color(N, N);
	for(int i = N - 1; i >= 0; i --)
		last_id[i] = last_color[C[i]], last_color[C[i]] = i;
	for(int i = 0; i < K; i ++)
		last_id[i + N] = last_color[i];

	vector<int> active(N, -1);
	set<pair<int, int> > s;
	for(int i = 0; i < K; i ++){
		active[i] = i + N;
		s.insert({last_id[i + N], i + N});
	}

	vector<int> ans(N + K, 0);
	for(int i = 0; i < N; i ++){
		if(active[C[i]] == -1){
			auto it = prev(s.end());
			ans[it -> second] = 1;
			if(it -> second > N) active[it -> second - N] = -1;
			else active[C[it -> second]] = -1;
			s.erase(it);
		}else{
			auto it = s.find({last_id[active[C[i]]], active[C[i]]});
			s.erase(it);
		}

		active[C[i]] = i;
		s.insert({last_id[i], i});
	}

	for(pair<int, int> i : s)
		ans[i.second] = 1;

	for(int i = 0; i < N + K; i ++)
		WriteAdvice(ans[i]);
}
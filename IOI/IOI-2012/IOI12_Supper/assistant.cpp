#include <vector>
#include <set>
#include "assistant.h"
using namespace std;

void Assist(unsigned char *A, int N, int K, int R) {
	set<int> current, active;
	for(int i = 0; i < K; i ++){
		current.insert(i);
		if(A[i + N])
			active.insert(i);
	}

	for(int nw, i = 0; i < N; i ++){
		nw = GetRequest();

		if(!current.count(nw)){
			int nx = *active.begin();
			current.erase(nx); active.erase(nx);
			PutBack(nx);
			current.insert(nw);
		}

		if(A[i]) active.insert(nw);
	}
}

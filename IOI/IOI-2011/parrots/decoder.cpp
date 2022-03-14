#include "decoder.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
using namespace std;

struct big__num{
	short arr[105];
	void init(int x){
		memset(arr, 0, sizeof(arr));
		arr[0] = (short)x;
	}
};
big__num operator+(big__num a, big__num b){
	for(int i = 0; i < 100; i ++){
		int tp = (int)a.arr[i] + (int)b.arr[i];
		if(tp >= 256){
			tp -= 256;
			a.arr[i + 1] ++;
		}
		a.arr[i] = (short)tp;
	}
	return a;
}
bool operator<(big__num a, big__num b){
	for(int i = 104; i >= 0; i --){
		if(a.arr[i] < b.arr[i]) return 1;
		if(a.arr[i] > b.arr[i]) return 0;
	}
	return 0;
}

big__num C_[605][605];
bool done_ = false;

void decode(int N, int L, int X[]){
	if(!done_){
		for(int i = 0; i < 605; i ++){
			C_[i][0].init(1);
			for(int j = 1; j <= i; j ++){
				C_[i][j].init(0);
				C_[i][j] = C_[i - 1][j] + C_[i - 1][j - 1];
			}
			for(int j = i + 1; j < 605; j ++)
				C_[i][j].init(0);
		}
		done_ = 1;
	}

	sort(X, X + L);

	big__num res; res.init(0);
	for(int i = 0; i < L; i ++)
		res = res + C_[5 * N + 255 - X[i] - i - 2][5 * N - i];
	for(int i = 0; i < N; i ++)
		output(res.arr[i]);
}
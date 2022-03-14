#include "encoder.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
using namespace std;

struct big_num{
	short arr[105];
	void init(int x){
		memset(arr, 0, sizeof(arr));
		arr[0] = (short)x;
	}
};
big_num operator+(big_num a, big_num b){
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
bool operator<(big_num a, big_num b){
	for(int i = 104; i >= 0; i --){
		if(a.arr[i] < b.arr[i]) return 1;
		if(a.arr[i] > b.arr[i]) return 0;
	}
	return 0;
}

big_num C[605][605];
bool done = false;

void encode(int N, int M[]){
	if(!done){
		for(int i = 0; i < 605; i ++){
			C[i][0].init(1);
			for(int j = 1; j <= i; j ++){
				C[i][j].init(0);
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			}
			for(int j = i + 1; j < 605; j ++)
				C[i][j].init(0);
		}
		done = 1;
	}

	big_num base, nw;
	nw.init(0); base.init(0);
	for(int i = 0; i < N; i ++) nw.arr[i] = M[i];
	nw = nw + base;
	base.init(0);
	int len = 255 + 5 * N;
	for(int i = 0; i < 5 * N; i ++){
		while(nw < C[len - 1][5 * N - i] + base) len --;
		send(5 * N + 255 - len - i - 1);
		base = base + C[len - 1][5 * N - i];
		len --;
	}
}
#include <bits/stdc++.h>
#include "dna.h"
using namespace std;

string a, b;

const int MX = 1e5 + 5;
int n, dna[MX][6]; // AC, AT, CA, CT, TA, TC
int cnta[MX][3], cntb[MX][3]; // A, C, T

void init(string _a, string _b){
	a = _a; b = _b;
	n = a.size();

	for(int i = 0; i < n; i ++){
		if(i > 0){
			for(int j = 0; j < 6; j ++)
				dna[i][j] = dna[i - 1][j];
			for(int j = 0; j < 3; j ++){
				cnta[i][j] = cnta[i - 1][j];
				cntb[i][j] = cntb[i - 1][j];
			}
		}

		if(a[i] == 'A'){
			cnta[i][0] ++;
			if(b[i] == 'A') cntb[i][0] ++;
			if(b[i] == 'C') dna[i][0] ++, cntb[i][1] ++;
			if(b[i] == 'T') dna[i][1] ++, cntb[i][2] ++;
		}
		if(a[i] == 'C'){
			cnta[i][1] ++;
			if(b[i] == 'A') dna[i][2] ++, cntb[i][0] ++;
			if(b[i] == 'C') cntb[i][1] ++;
			if(b[i] == 'T') dna[i][3] ++, cntb[i][2] ++;
		}
		if(a[i] == 'T'){
			cnta[i][2] ++;
			if(b[i] == 'A') dna[i][4] ++, cntb[i][0] ++;
			if(b[i] == 'C') dna[i][5] ++, cntb[i][1] ++;
			if(b[i] == 'T') cntb[i][2] ++;
		}
	}
}

int get_distance(int x, int y){
	int ac = dna[y][0] - (x > 0 ? dna[x - 1][0] : 0);
	int at = dna[y][1] - (x > 0 ? dna[x - 1][1] : 0);
	int ca = dna[y][2] - (x > 0 ? dna[x - 1][2] : 0);
	int ct = dna[y][3] - (x > 0 ? dna[x - 1][3] : 0);
	int ta = dna[y][4] - (x > 0 ? dna[x - 1][4] : 0);
	int tc = dna[y][5] - (x > 0 ? dna[x - 1][5] : 0);

	for(int j = 0; j < 3; j ++){
		int cntA = cnta[y][j] - (x > 0 ? cnta[x - 1][j] : 0);
		int cntB = cntb[y][j] - (x > 0 ? cntb[x - 1][j] : 0);
		if(cntA != cntB) return -1;
	}

	return min(ac, ca) + min(at, ta) + min(ct, tc) + ((abs(ac - ca) + abs(at - ta) + abs(ct - tc)) * 2) / 3;
}

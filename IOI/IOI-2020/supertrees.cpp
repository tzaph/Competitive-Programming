#include "supertrees.h"
#include <vector>
using namespace std;
 
int construct(vector<vector<int>> p) {
	int n = p.size();
	vector<vector<int>> ans(n, vector<int>(n, 0));
 
	for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++)
		if(p[i][j] == 3) return 0;
 
	vector<int> rt(n, 0);
 
	for(int i = 0; i < n; i ++){
		int la = 0;
		for(; p[i][la] != 1; la ++);
 
		if(la != i){
			if(p[la] != p[i]) return 0;
			ans[la][i] = 1; ans[i][la] = 1;
		}else rt[i] = 1;
	}
 
	for(int i = 0; i < n; i ++) if(rt[i]){
		int cc = 0;
		for(; p[i][cc] == 0; cc ++);
		for(int j = 0; j < n; j ++)
			if((p[cc][j] == 0) ^ (p[i][j] == 0))
				return 0;
 
		if(cc == i){
			int la = i;
			for(int j = i + 1; j < n; j ++)
				if(rt[j] && p[i][j]){
					ans[la][j] = 1; ans[j][la] = 1;
					la = j;
				}
 
			if(la == i);
			else if(ans[la][i]) return 0;
			else{
				ans[la][i] = 1; ans[i][la] = 1;
			}
		}
	}
 
	build(ans);
	return 1;
}
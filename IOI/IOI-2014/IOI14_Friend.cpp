#include"friend.h"
#include<bits/stdc++.h>
using namespace std;
int findSample(int n, int c[], int h[], int p[]){
	int ans[n], alt[n];
	memset(alt, 0, sizeof(alt));
	for(int i=0; i<n; i++) ans[i]=c[i];
	for(int i=n-1; i>0; i--){
		if(p[i]==0){
			ans[h[i]]+=alt[i];
			alt[h[i]]+=ans[i];
		}else if(p[i]==1){
			ans[h[i]]+=ans[i];
			alt[h[i]]+=alt[i];
		}else if(p[i]==2){
			ans[h[i]]=max(ans[h[i]]+alt[i], alt[h[i]]+ans[i]);
			alt[h[i]]+=alt[i];
		}
		ans[h[i]]=max(ans[h[i]], alt[h[i]]);
	}
	return ans[0];
}
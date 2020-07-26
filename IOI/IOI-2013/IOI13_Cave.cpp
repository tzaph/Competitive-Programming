#include "cave.h"
#include<bits/stdc++.h>
using namespace std;
int s[5069], d[5069];
bool vis[5069];
void flipLever(int l, int r){
	for(int i=l; i<=r; i++) 
		if(!vis[i]) s[i]=1-s[i];
}
int findLever(int door, int n){
	int l=0, r=n-1;
	if(tryCombination(s)!=door) 
		flipLever(l, r);
	while(l<r){
		int md=(l+r)/2;
		flipLever(l, md);
		int tmp=tryCombination(s);
		flipLever(l, md);
		if(tmp!=door) r=md;
		else l=md+1;
	}
	return l;
}
void exploreCave(int n){
	for(int i=0; i<n; i++){
		int lv=findLever(i, n);
		s[lv]=1-s[lv];
		d[lv]=i; vis[lv]=true;
	}
	answer(s, d);
}
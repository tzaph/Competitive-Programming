#include "gondola.h"
#include<bits/stdc++.h>
using namespace std;
 
int valid(int n, int inputSeq[]){
	map<int, bool>mp;
	for(int i=0; i<n; i++){
		if(!mp[inputSeq[i]])
			mp[inputSeq[i]]=true;
		else return 0;
	}
	int fi=-1;
	for(int i=0; i<n; i++){
		if(inputSeq[i]<=n){
			if(fi==-1) fi=i;
			else{
				int check=i+inputSeq[fi]-fi;
				check%=n;
				if(check==0) check=n;
				if(check!=inputSeq[i]) return 0;
			}
		}
	}
	return 1;
}
 
int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	int rotate=0;
	for(int i=0; i<n; i++){
		if(gondolaSeq[i]<=n) rotate=(n+gondolaSeq[i]-i-1)%n;
	}
	int now;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
	for(int i=0; i<n; i++){
		now=gondolaSeq[(n+i-rotate)%n];
		if(now>n) pq.push({now, i+1});
	}
	int idx=0, cnt=n+1;
	while(!pq.empty()){
		int replacementGondola=pq.top().first;
		int idxc=pq.top().second;
		pq.pop();
		replacementSeq[idx++]=idxc;
		for(int i=cnt; i<replacementGondola; i++){
			replacementSeq[idx++]=i;
		}
		cnt=replacementGondola+1;
	}
	return idx;
}
 
const long long mod=1000000009;
long long mdx(long long b, long long e){
	long long res=1ll; b%=mod;
	while(e>0){
		if(e&1) res=(res*b)%mod;
		e>>=1ll; b=(b*b)%mod;
	}
	return res;
}
int countReplacement(int n, int inputSeq[]){
	if(!valid(n, inputSeq)) return 0;
	int more[100069]={};
	int idxcnt=0;
	for(int i=0; i<n; i++)
		if(inputSeq[i]>n) more[idxcnt++]=inputSeq[i];
	long long res=1ll;
	if(idxcnt==n) res=(long long)n;
	if(idxcnt==0) return 1;
	int cnt=idxcnt, last=n;
	sort(more, more+idxcnt);
	for(int i=0; i<idxcnt; i++){
		res=(res*mdx((long long)cnt, (long long)(more[i]-last-1)))%mod;
		last=more[i]; cnt--;
	}
	return (int)res;
}
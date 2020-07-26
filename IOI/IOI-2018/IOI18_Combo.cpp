#include "combo.h"
#include<bits/stdc++.h>
using namespace std;

string guess_sequence(int N){
	string res="";
	if(press("AB")>=1){
		if(press("A")) res="A";
		else res="B";
	}else{
		if(press("X")) res="X";
		else res="Y";
	}
	if(N==1) return res;
	vector<char>c={'A','B','X','Y'};
	c.erase(find(c.begin(), c.end(), res[0]));
	while(res.size()<=N-2){
		int op=press(res+c[0]+c[0] +res+c[0]+c[1] +res+c[1]+c[0]);
		if(op==res.size()){
			res=res+c[2];
		}else if(op==res.size()+1){
			op=press(res+c[1]+c[2]);
			if(op==res.size()) res=res+c[0]+c[2];
			else if(op==res.size()+1) res=res+c[1]+c[1];
			else res=res+c[1]+c[2];
		}else{
			op=press(res+c[0]+c[1]);
			if(op==res.size()) res=res+c[1]+c[0];
			else if(op==res.size()+1) res=res+c[0]+c[0];
			else res=res+c[0]+c[1];
		}
	}
	while(res.size()!=N){
		if(press(res+c[0])==res.size()+1) res=res+c[0];
		else if(press(res+c[1])==res.size()+1) res=res+c[1];
		else res=res+c[2];
	}
	return res;
}
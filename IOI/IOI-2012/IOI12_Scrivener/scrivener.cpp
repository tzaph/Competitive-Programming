#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int MX = 1000005;

int ver[MX], sz[MX], L[MX * 21], R[MX * 21], cnt = 0;
char st[MX * 21];
int current_ver = 0;

int copyNode(int nw){
	cnt ++;
	st[cnt] = st[nw];
	L[cnt] = L[nw];
	R[cnt] = R[nw];
	return cnt;
}

int build(int cl, int cr){
	int nw = ++ cnt;
	if(cl == cr) return nw;
	L[nw] = build(cl, (cl + cr) / 2);
	R[nw] = build((cl + cr) / 2 + 1, cr);
	return nw;
}

int upd(int nw, int cl, int cr, int ps, char v){
	nw = copyNode(nw);
	if(cl == cr){
		st[nw] = v;
		return nw;
	}

	if(ps <= (cl + cr) / 2)
		L[nw] = upd(L[nw], cl, (cl + cr) / 2, ps, v);
	else
		R[nw] = upd(R[nw], (cl + cr) / 2 + 1, cr, ps, v);

	st[nw] = max(st[L[nw]], st[R[nw]]);
	return nw;
}

char que(int nw, int cl, int cr, int ps){
	if(cl == cr) return st[nw];
	if(ps <= (cl + cr) / 2)
		return que(L[nw], cl, (cl + cr) / 2, ps);
	return que(R[nw], (cl + cr) / 2 + 1, cr, ps);
}

void Init(){
	current_ver ++;
	ver[current_ver] = build(0, MX - 1);
	sz[current_ver] = 0;
}

void TypeLetter(char cc){
	int last_ver = current_ver;
	current_ver ++;
	ver[current_ver] = upd(ver[last_ver], 0, MX - 1, sz[last_ver], cc);
	sz[current_ver] = sz[last_ver] + 1;
}

void UndoCommands(int U){
	int last_ver = max(current_ver - U, 1);
	current_ver ++;
	ver[current_ver] = ver[last_ver];
	sz[current_ver] = sz[last_ver];
}

char GetLetter(int P){
	return que(ver[current_ver], 0, MX - 1, P);
}
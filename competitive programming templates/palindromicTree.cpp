#include <bits/stdc++.h>
using namespace std;

const int MX = 100005;

struct palindromic_tree{
	struct node{
		int nxt[26], suff_link, len, cnt;
		vector<int> edges;
	} tree[MX];

	string s;
	int suff, num;

	void add_letter(int pos){
		int cr = suff;
		int cr_len = 0;
		int letter = s[pos] - 'a';

		for(;;){
			cr_len = tree[cr].len;
			if(pos - 1 - cr_len >= 0 && s[pos - 1 - cr_len] == s[pos]) 
				break;
			cr = tree[cr].suff_link;
		}

		if(tree[cr].nxt[letter]){
			suff = tree[cr].nxt[letter];
			tree[suff].cnt ++;
			return;
		}

		suff = num + 1; num ++;
		tree[num].len = tree[cr].len + 2;
		tree[num].cnt = 1;
		tree[cr].nxt[letter] = num;

		if(tree[num].len == 1){
			tree[num].suff_link = 2;
			tree[2].edges.push_back(num);
			return;
		}

		for(;;){
			cr = tree[cr].suff_link;
			cr_len = tree[cr].len;

			if(pos - 1 - cr_len >= 0 && s[pos - 1 - cr_len] == s[pos]){
				tree[num].suff_link = tree[cr].nxt[letter];
				tree[tree[cr].nxt[letter]].edges.push_back(num);
				break;
			}
		}
	}

	void init(){
		num = 2; suff = 2;
		tree[1].len = -1; tree[1].suff_link = 1;
		tree[2].len = 0; tree[2].suff_link = 1;
		tree[1].edges.push_back(2);
	}

	void dfs_cnt(int nw = 1){
		for(int nx : tree[nw].edges){
			dfs_cnt(nx);
			tree[nw].cnt += tree[nx].cnt;
		}
	}
} pt;

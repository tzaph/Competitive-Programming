#include "scales.h"
#include <vector>
#include <algorithm>
using namespace std;

int pw3[] = {243, 81, 27, 9, 3, 1};

struct ord{
	int a[7];
	ord(vector<int> v){
		for(int i = 0; i < 6; i ++)
			a[i + 1] = v[i];
	}
};

struct query{
	int a, b, c, d;

	int ask(){
		int rs;
		if(d == a) rs = getLightest(a, b, c);
		else if(d == b) rs = getMedian(a, b, c);
		else if(d == c) rs = getHeaviest(a, b, c);
		else rs = getNextLightest(a, b, c, d);

		if(rs == a) return 0;
		if(rs == b) return 1;
		return 2;
	}

	int simulate_ask(ord v){
		int x = a, y = b, z = c, rs;
		if(v.a[x] > v.a[y]) swap(x, y);
		if(v.a[y] > v.a[z]) swap(y, z);
		if(v.a[x] > v.a[y]) swap(x, y);

		if(d == a) rs = x;
		else if(d == b) rs = y;
		else if(d == c) rs = z;
		else{
			if(v.a[d] < v.a[x]) rs = x;
			else if(v.a[d] < v.a[y]) rs = y;
			else if(v.a[d] < v.a[z]) rs = z;
			else rs = x;
		}

		if(rs == a) return 0;
		if(rs == b) return 1;
		return 2;
	}
};

vector<query> all_queries;

struct tree{
	int ht, nd;
	vector<ord*> possible;
	query* opt;
	tree* child[3];

	bool init(){
		if(possible.size() <= 1) return true;

		for(query &q : all_queries){
			vector<int> cnt(3, 0);

			for(ord* i : possible){
				int rs = q.simulate_ask(*i);
				cnt[rs] ++;
			}

			if(max(max(cnt[0], cnt[1]), cnt[2]) > pw3[ht]) continue;

			for(int i = 0; i < 3; i ++){
				child[i] = new tree();
				child[i] -> ht = ht + 1;
				child[i] -> nd = 3 * nd - 1 + i;
			}

			for(ord* i : possible) 
				child[q.simulate_ask(*i)] -> possible.push_back(i);

			bool good = true;
			for(int i = 0; i < 3; i ++)
				good &= child[i] -> init();

			if(!good){
				for(int i = 0; i < 3; i ++)
					delete child[i];
			}else{
				opt = &q;
				return true;
			}
		}

		return false;
	}
};

tree *root;

void init(int T){
	for(int i = 1; i <= 4; i++)
		for(int j = i + 1; j <= 5; j ++)
			for(int k = j + 1; k <= 6; k ++)
				for(int l = 1; l <= 6; l ++)
					all_queries.push_back((query){i, j, k, l});


	root = new tree();
	root -> ht = 0;
	root -> nd = 1;

	vector<int> perm = {1, 2, 3, 4, 5, 6};
	do{
		root -> possible.push_back(new ord(perm));
	}while(next_permutation(perm.begin(), perm.end()));

	root -> init();
}

void orderCoins(){
	int w[] = {1, 2, 3, 4, 5, 6};

	tree* ans = root;
	while(ans -> possible.size() != 1)
		ans = ans -> child[ans -> opt -> ask()];

	for(int i = 1; i <= 6; i ++)
		w[ans -> possible[0] -> a[i] - 1] = i;

	answer(w);
}
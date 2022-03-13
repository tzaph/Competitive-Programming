#include <vector>
#include <array>
#include <string>
#include <queue>
using namespace std;

struct aho_corasick{
	static const int alpha = 26;

	vector<array<int, alpha> > go;
	vector<int> link, end_pos;

	aho_corasick(){add_node();}

	int add_string(string s){
		int nw = 0;
		for(char c : s){
			if(!go[nw][c - 'a']){
				int get = add_node();
				go[nw][c - 'a'] = get;
			}
			nw = go[nw][c - 'a'];
		}
		end_pos[nw] ++;
		return nw;
	}

	void build(){
		queue<int> q;
		for(int c = 0; c < alpha; c ++)
			if(go[0][c]) q.push(go[0][c]);

		for(int nw, u; !q.empty();){
			nw = q.front(); q.pop();
			u = link[nw];

			for(int c = 0; c < alpha; c ++){
				if(!go[nw][c]) go[nw][c] = go[u][c];
				else{
					link[go[nw][c]] = go[u][c];
					end_pos[go[nw][c]] += end_pos[go[u][c]];
					q.push(go[nw][c]);
				}
			}
		}
	}

	int add_node(){
		int ps = go.size();
		go.emplace_back(array<int, alpha>());
		link.emplace_back(0);
		end_pos.emplace_back(0);
		return ps;
	}
} ac;
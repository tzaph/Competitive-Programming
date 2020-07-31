/*
	* IOI 2017 Nowruz
	* Basicly A* with heuristic = max number of leaves that can be made
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, int> pii;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
const char BLOCK = '#';
const char OPEN = '.';
const char TREE = 'X';

struct nowruz{
	int n, m;
	string grid[1030];

	set<pair<int, pii> > s;

	char grd(pii p){return grid[p.first][p.second];}
	bool inside(pii p){return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;}
	bool open(pii p){return inside(p) && grd(p) == OPEN;}
	pii adj(pii p, int d){return pii(p.first + dx[d], p.second + dy[d]);}

	int around(pii p, char ch){
		int cnt = 0;
		for(int d = 0; d < 4; d ++){
			if(inside(adj(p, d)) && grd(adj(p, d)) == ch) cnt ++;
			else if(!inside(adj(p, d)) && ch == BLOCK) cnt ++;
		}
		return cnt;
	}

	int extend(pii p, bool act){
		if(!open(p) || around(p, TREE) != 1) return - 1;

		int cnt = 0;
		for(int d = 0; d < 4; d ++) if(open(adj(p, d))){
			if(around(adj(p, d), TREE) == 0){
				if(act) add(adj(p, d));
				cnt ++;
			}
		}
		if(act) grid[p.first][p.second] = TREE;

		return cnt;
	}

	void add(pii p){
		grid[p.first][p.second] = TREE;
		for(int d = 0; d < 4; d ++) if(open(adj(p, d))){
			int cnt = extend(adj(p, d), 0);
			if(cnt != -1) s.insert({cnt, adj(p, d)});
		}
	}

	vector<int> mark[1030];
	int timer = 1;
	queue<pii> q;

	int cnt_size(int x, int y){
		int sz = 1; timer ++;
		mark[x][y] = timer;

		q.push(pii(x, y));
		for(; !q.empty();){
			pii p = q.front(); q.pop();
			for(int d = 0; d < 4; d ++){
				if(open(adj(p, d)) && mark[p.first + dx[d]][p.second + dy[d]] != timer){
					mark[p.first + dx[d]][p.second + dy[d]] = timer;
					q.push(adj(p, d));
					sz ++;
				}
			}
		}

		return sz;
	}

	void init(){
		for(int i = 0; i < n; i ++)
			mark[i].assign(1030, 0);

		pii st;
		int best_cnt = -1;
		for(int i = 0; i < n; i ++) for(int j = 0; j < m; j ++) if(!mark[i][j] && grid[i][j] == OPEN){
			int nw = cnt_size(i, j);
			if(nw > best_cnt){
				best_cnt = nw;
				st = {i, j};
			}
		}

		add(st);
	}

	bool is_path;
	int dfs(int x, int y, bool st = true){
		if(!open({x, y}) || (!st && around({x, y}, TREE) > 0) || mark[x][y] == timer) return 0;

		mark[x][y] = timer;
		int rs = 1, cnt = 0;
		for(int d = 0; d < 4; d ++){
			int tmp = rs;
			rs += dfs(x + dx[d], y + dy[d], false);
			if(rs > tmp) cnt ++;
		}
		if(cnt >= 2) is_path = false;
		return rs;
	}

	void solve(){
		init();

		for(;;){
			while(!s.empty()){
				auto t = *s.rbegin();
				s.erase(t);

				int cnt = extend(t.second, 0);
				if(cnt == t.first)
					extend(t.second, 1);
				else if(cnt != -1)
					s.insert({cnt, t.second});
			}

			bool changed = false;
			for(int i = 0; i < n; i ++) if(!changed)
				for(int j = 0; j < m; j ++) if(!changed && grid[i][j] == OPEN && around({i, j}, TREE) == 1){
					add({i, j});
					changed = true;
				}

			for(int i = 0; i < n; i ++) if(!changed)
				for(int j = 0; j < m; j ++) if(!changed && grid[i][j] == OPEN && around({i, j}, TREE) == 2){
					int cnt = 0;
					for(int d = 0; d < 4; d ++){
						if(inside(adj({i, j}, d)) && grd(adj({i, j}, d)) == OPEN && around(adj({i, j}, d), TREE) == 0)
							cnt ++;
					}

					if(cnt < 2) continue;

					for(int d = 0; d < 4; d ++){
						if(inside(adj({i, j}, d)) && grd(adj({i, j}, d)) == TREE && around(adj({i, j}, d), TREE) == 1){
							grid[adj({i, j}, d).first][adj({i, j}, d).second] = OPEN;
							add({i, j});
							changed = true;
							break;
						}
					}
				}

			for(int i = 0; i < n; i ++) if(!changed)
				for(int j = 0; j < m; j ++) if(!changed && grid[i][j] == OPEN && around({i, j}, TREE) == 2){
					timer ++; is_path = true;
					int sz = dfs(i, j);

					int cnt = 0;
					for(int d = 0; d < 4; d ++){
						if(inside(adj({i, j}, d)) && grd(adj({i, j}, d)) == TREE && around(adj({i, j}, d), TREE) == 1)
							cnt ++;
					}

					if((cnt == 2 && sz < 7) || sz < 4) continue;

					for(int d = 0; d < 4; d ++){
						if(inside(adj({i, j}, d)) && grd(adj({i, j}, d)) == TREE && around(adj({i, j}, d), TREE) == 1){
							grid[adj({i, j}, d).first][adj({i, j}, d).second] = OPEN;
							add({i, j});
							changed = true;
							break;
						}
					}
				}

			if(!changed) break;
		}
	}

	void read(){
		cin >> n >> m;
		int tmp; cin >> tmp;
		for(int i = 0; i < n; i ++)
			cin >> grid[i];
	}

	void write(){
		for(int i = 0; i < n; i ++) for(int j = 0; j < m; j ++)
			if(grid[i][j] == OPEN || grid[i][j] == TREE)
				grid[i][j] ^= 'X' ^ '.';
		for(int i = 0; i < n; i ++) cout << grid[i] << endl;
	}
};

int main(){
	nowruz sol;
	sol.read();
	sol.solve();
	sol.write();
	return 0;
}
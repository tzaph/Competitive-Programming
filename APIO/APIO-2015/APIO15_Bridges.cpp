#include <bits/stdc++.h>
using namespace std;

#define ll long long
int k, n;
vector<pair<int, int> > p;
ll ans = 0ll;

ll solvek1(){
	if(p.empty()) return 0ll;

	ll res = 0ll;
	vector<int> cr;
	for(int i = 0; i < p.size(); i ++){
		cr.push_back(p[i].first);
		cr.push_back(p[i].second);
		res -= (ll)(p[i].first + p[i].second);
	}

	sort(cr.begin(), cr.end());
	for(int i = 2 * (int)p.size() - 1; i >= (int)p.size(); i --)
		res += 2ll * cr[i];

	return res + (int)p.size();
}

bool cmp(pair<int, int> a, pair<int, int> b){
	return a.first + a.second < b.first + b.second;
}

vector<ll> comp(){
	priority_queue<int> mx;
	priority_queue<int, vector<int>, greater<int> > mn;
	ll sum_mx = (ll)p[0].first, sum_mn = (ll)p[0].second;

	mx.push((int)sum_mx); mn.push((int)sum_mn);
	vector<ll> tmp; tmp.push_back(sum_mn - sum_mx);

	for(int i = 1; i < p.size(); i ++){
		int mxt = mx.top(), mnt = mn.top();
		int lf = p[i].first, rg = p[i].second;
		if(lf <= mxt && rg <= mxt){
			mx.pop();
			mx.push(lf); mx.push(rg);
			mn.push(mxt);
			sum_mx += lf + rg - mxt;
			sum_mn += mxt;
		}else if(lf >= mnt && rg >= mnt){
			mn.pop();
			mn.push(lf); mn.push(rg);
			mx.push(mnt);
			sum_mn += lf + rg - mnt;
			sum_mx += mnt;
		}else{
			mx.push(lf); mn.push(rg);
			sum_mx += lf; sum_mn += rg;
		}
		tmp.push_back(sum_mn - sum_mx);
	}
	
	return tmp;
}

ll solvek2(){
	if(p.empty()) return 0ll;

	sort(p.begin(), p.end(), cmp);
	vector<ll> asc = comp();
	reverse(p.begin(), p.end());
	vector<ll> dec = comp();

	ll res = 1e18;
	for(int i = 0; i < (int)p.size() - 1; i ++)
		res = min(res, asc[i] + dec[(int)p.size() - i - 2]);
	return min(res + (ll)p.size(), solvek1());
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> k >> n;
	for(int i = 0; i < n; i ++){
		string tp1, tp2; int p1, p2;
		cin >> tp1 >> p1 >> tp2 >> p2;
		if(tp1 == tp2)
			ans += (ll)abs(p1 - p2);
		else
			p.push_back({min(p1, p2), max(p1, p2)});
	}

	cout << ans + (k == 1 ? solvek1() : solvek2()) << endl;
	return 0;
}
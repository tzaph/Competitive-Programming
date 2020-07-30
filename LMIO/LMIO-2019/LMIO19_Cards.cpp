/*
	* LMIO 2019 Cards
	* Main Idea : Inclusion Exclusion
	* Explanations are in the code
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ll long long
ll ans;
ll up[26 * 26 + 5], dn[26 * 26 + 5], lf[26 * 26 + 5], rg[26 * 26 + 5];
int oc[(26 * 26 + 5) * (26 * 26 + 5)];

int hash2(int a, int b){return 26 * a + b;}
int hash4(int a, int b, int c, int d){
	return 26 * 26 * 26 * a + 26 * 26 * b + 26 * c + d;
}

int n;
vector<string> v;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for(int i = 0; i < n; i ++){
		string a, b;
		cin >> a >> b;
		v.push_back(a + b);
	}

	for(string i : v){
		oc[hash4(i[0] - 'A', i[1] - 'A', i[2] - 'A', i[3] - 'A')] ++;
		up[hash2(i[0] - 'A', i[1] - 'A')] ++;
		dn[hash2(i[2] - 'A', i[3] - 'A')] ++;
		lf[hash2(i[0] - 'A', i[2] - 'A')] ++;
		rg[hash2(i[1] - 'A', i[3] - 'A')] ++;
	}

	//all cases (+)
	for(int i = 0; i < 26 * 26; i ++)
		ans += up[i] * dn[i] + lf[i] * rg[i];

	//two duplicate opposite (-)
	for(int a = 0; a < 26; a ++) for(int b = 0; b < 26; b ++){
		for(int c = 0; c < 26; c ++) for(int d = 0; d < 26; d ++){
			int fi = hash4(a, b, c, d), sc = hash4(b, a, d, c);
			if(fi < sc) ans -= oc[fi] * oc[sc];
			sc = hash4(c, d, a, b);
			if(fi < sc) ans -= oc[fi] * oc[sc];
		}
	}

	//two duplicate adjacent (-)
	for(int a = 0; a < 26; a ++) for(int b = 0; b < 26; b ++){
		for(int c = 0; c < 26; c ++) for(int d = 0; d < 26; d ++){
			int fi = hash4(c, a, a, b), sc = hash4(a, b, b, d);
			if(fi != sc) ans -= oc[fi] * oc[sc];
			fi = hash4(a, b, c, a), sc = hash4(b, d, a, b);
			if(fi != sc) ans -= oc[fi] * oc[sc];
		}
	}

	//four duplicate (+)
	for(int a = 0; a < 26; a ++) for(int b = a + 1; b < 26; b ++){
		int fi = hash4(a, b, b, a), sc = hash4(b, a, a, b);
		ans += 3 * oc[fi] * oc[sc];
	}

	//self intersecting (-)
	for(int a = 0; a < 26; a ++)
		ans -= 2 * oc[hash4(a, a, a, a)];
	for(int a = 0; a < 26; a ++) for(int b = 0; b < 26; b ++) if(a != b){
		ans -= oc[hash4(a, b, a, b)] + oc[hash4(a, a, b, b)];
	}

	cout << ans << endl;
	return 0;
}

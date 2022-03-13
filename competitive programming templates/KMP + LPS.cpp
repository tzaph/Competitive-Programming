#include <vector>
#include <string>
using namespace std;

vector<int> prefix_function(string s){
	vector<int> lps(s.size(), 0);
	for(int i = 1, j = 0; i < s.size(); i ++){
		for(; j && s[i] != s[j]; j = lps[j - 1]);
		j += (s[i] == s[j]);
		lps[i] = j;
	}
	return lps;
}

vector<int> occ(string text, string patt){ // KMP
	vector<int> ans, lps = prefix_function(patt);

	for(int i = 0, j = 0; i < text.size(); i ++){
		for(; j && text[i] != patt[j]; j = lps[j - 1]);
		j += (text[i] == patt[j]);

		if(j == patt.size()){
			ans.push_back(i - j + 1);
			j = lps[j - 1];
		}
	}

	return ans;
}
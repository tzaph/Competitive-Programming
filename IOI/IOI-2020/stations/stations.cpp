#include "stations.h"
#include <vector>
#include <algorithm>
using namespace std;

int find_next_station(int s, int t, vector<int> c){
	if(c.back() < s) reverse(c.begin(), c.end());
	for(int i : c)
		if(min(i, s) <= t && t <= max(i, s))
			return i;
	return c.back();
}
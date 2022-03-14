#include "sorting.h"
#include <bitset>
#include <algorithm>
#include <vector>
using namespace std;

int n, v[200005], pos[200005];
bitset<200005> vis;

void dfs(int nw, int init){
    vis[nw] = 1;
    if(nw == init) return;
    dfs(v[nw], init);
}

vector<pair<int, int> > swp;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    n = N;
    for(int i = 0; i < n; i ++){
        v[i] = S[i];
        pos[v[i]] = i;
    }

    int lf = 0, rg = M, res;
    for(int md; lf <= rg;){
        md = (lf + rg) / 2;
        for(int i = 0; i < md; i ++)
            swap(v[X[i]], v[Y[i]]);

        int cc = 0;
        for(int i = 0; i < n; i ++) if(!vis[i]){
            dfs(v[i], i); cc ++;
        }

        if(n - cc <= md){
            res = md; rg = md - 1;
        }else lf = md + 1;

        vis = 0;
        for(int i = 0; i < n; i ++)
            v[i] = S[i];
    }

    for(int i = 0; i < res; i ++)
        swap(v[X[i]], v[Y[i]]);
    for(int i = 0; i < n; i ++)
        while(v[i] != i){
            swp.push_back({v[i], i});
            swap(v[i], v[v[i]]);
        }

    for(int i = 0; i < res; i ++){
        swap(S[X[i]], S[Y[i]]);
        swap(pos[S[X[i]]], pos[S[Y[i]]]);
        if(swp.empty()) P[i] = 0, Q[i] = 0;
        else{
            P[i] = pos[swp.back().first], Q[i] = pos[swp.back().second];
            swap(S[P[i]], S[Q[i]]);
            swap(pos[S[P[i]]], pos[S[Q[i]]]);
            swp.pop_back();
        } 
    }

    return res;
}
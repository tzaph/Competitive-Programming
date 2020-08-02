#include "koala.h"
#include <bits/stdc++.h>
using namespace std;
 
int a[105], b[105];
 
int minValue(int n, int w){
    for(int i = 1; i < n; i ++)
        a[i] = 0;
    a[0] = 1;
    playRound(a, b);
    for(int i = 0; i < n; i ++)
        if(a[i] >= b[i]) return i;
    return 0;
}
 
vector<int> large;
int maxValue(int n, int w){
    large.clear();
    for(int i = 0; i < n; i ++)
        large.push_back(i);
    for(; large.size() > 1;){
        for(int i = 0; i < n; i ++)
            a[i] = 0;
        int ct = w / large.size();
        for(int i : large)
            a[i] = ct;
 
        playRound(a, b);
 
        large.clear();
        for(int i = 0; i < n; i ++)
            if(b[i] > ct)
                large.push_back(i);
    }
    return large[0];
}
 
int n, w;
bool cmp(int x, int y){
    int lf = 1, rg = min(w / 2, 12);
    for(int md; lf <= rg;){
        md = (lf + rg) / 2;
        for(int i = 0; i < n; i ++)
            a[i] = 0;
        a[x] = a[y] = md;
        playRound(a, b);
        bool gt0 = b[x] > a[x];
        bool gt1 = b[y] > a[y];
        if(gt0 == gt1){
            if(gt1) lf = md + 1;
            else rg = md - 1;
        }else{
            if(gt1) return 1;
            else return 0;
        }
    }
    return 0;
}
 
int greaterValue(int N, int W){
    n = N, w = W;
    return cmp(0, 1);
}
 
int every[105];
 
void solve(int n, int w, vector<int> v, int l, int r){
    if(l > r) return;
    if(l == r) return void(every[v[0]] = l);
    int ct = min((int)sqrt(2 * l), min(w / (r - l + 1), 8));
 
    for(int i = 0; i < n; i ++)
        a[i] = 0;
    for(int i : v)
        a[i] = ct;
    playRound(a, b);
    vector<int> lf, rg;
    for(int i : v){
        if(b[i] > ct) rg.push_back(i);
        else lf.push_back(i);
    }
 
    solve(n, w, lf, l, l + (int)lf.size() - 1);
    solve(n, w, rg, r - (int)rg.size() + 1, r);
}
 
void allValues(int N, int W, int *P){
    n = N, w = W;
    if(W == N * 2){
        //sub4
        vector<int> tmp(n);
        for(int i = 0; i < n; i ++)
            tmp[i] = i;
        stable_sort(tmp.begin(), tmp.end(), [&](int x, int y){
            for(int i = 0; i < n; i ++) a[i] = 0;
            a[x] = a[y] = n;
            playRound(a, b);
            return b[x] < b[y];
        });
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j ++)
                if(tmp[j] == i) P[i] = j + 1;
        }
    }else{
        //sub5
        vector<int> v(n);
        iota(v.begin(), v.end(), 0);
        solve(n, w, v, 1, n);
        for(int i = 0; i < n; i ++)
            P[i] = every[i];
    }
}
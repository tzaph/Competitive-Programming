struct line{
    ll m, c;
    ll eval(ll x) {return m * x + c;}
    ld intersectX(line l){
        return (ld) (c - l.c) / (l.m - m);
    }
};

deque<line> dq;
int ptr = 0;

dq.push_back(base_case);
for(int i = 1; i < n; i ++){
    if(ptr >= dq.size()) ptr = dq.size() - 1;
    for(; ptr + 1 < dq.size() && dq[ptr].eval(que[i]) < dq[ptr + 1].eval(que[i]); ptr ++);
    dp[i] = constant + dq[ptr].eval(que[i]);
    line cs = (line){gradient, constant + dp[i]};
    dq.push_back(cs);
    while(dq.size() >= 3 && dq[dq.size() - 3].intersectX(dq[dq.size() - 1]) >= dq[dq.size() - 2].intersectX(dq[dq.size() - 1])){
        cs = dq.back(); dq.pop_back();
        dq.pop_back(); dq.push_back(cs);
    }
}

// gradient decreasing, query increasing, maximize
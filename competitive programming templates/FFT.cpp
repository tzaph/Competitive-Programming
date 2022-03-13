// For addition reference, please check NTT.cpp

#define ld double
#define cd complex<ld>
const ld pi = acos(-1.0);

void fft(vector<cd> &v, bool invert){
    int n = v.size();
    for(int i = 1, j = 0; i < n; i ++){
        int bt = n >> 1;
        for(; j & bt; bt >>= 1) j ^= bt;
        j ^= bt;

        if(i < j) swap(v[i], v[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        ld ang = 2 * pi / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));

        for(int i = 0; i < n; i += len){
            cd w(1);
            for(int j = 0; j < len / 2; j ++){
                cd uu = v[i + j], vv = v[i + j + len / 2] * w;
                v[i + j] = uu + vv; v[i + j + len / 2] = uu - vv;
                w *= wlen;
            }
        }
    }

    if(invert)
        for(cd &i : v) i /= n;
}

vector<int> multiply(vector<int> const& a, vector<int> const&b){
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size() + b.size()) n *= 2;
    fa.resize(n); fb.resize(n);

    fft(fa, false); fft(fb, false);
    for(int i = 0; i < n; i ++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> res(n);
    for(int i = 0; i < n; i ++)
        res[i] = round(fa[i].real());
    return res;
}
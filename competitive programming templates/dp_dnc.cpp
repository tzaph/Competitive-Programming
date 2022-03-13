void dp_dnc(int lf, int rg, int optl, int optr, int kk){
	if(lf > rg) return;
	
	int opt = -1, md = (lf + rg) / 2;
	for(int i = optl; i <= min(md, optr); i ++){
		if(dp[i - 1][kk - 1] + cost(i, md) < dp[md][kk]){
			opt = i;
			dp[md][kk] = dp[i - 1][kk - 1] + cost(i, md);
		}
	}
 
	dp_dnc(lf, md - 1, optl, opt, kk);
	dp_dnc(md + 1, rg, opt, optr, kk);
}

for(int j = 0; j < n; j ++)
	dp[j][1] = cost(0, j);

for(int i = 2; i <= k; i ++){
	for(int j = 0; j < n; j ++)
		dp[j][i] = mod * 1ll * mod;
	dp_dnc(i - 1, n - 1, i - 1, n - 1,  i);
}
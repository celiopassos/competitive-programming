// Knuth's dp optimization
// dp[i][j] = min(dp[i][k] + dp[k+1][j]) + C(i, j)
// necessary condition: C(i, j - 1) <= C(i, j) <= C(i + 1, j)
// complexity: O(n^2)

void knuth(){
	for(int i = 0; i < n; i++)opt[i][i] = i;
	for(int d = 1; d < n; d++){
		for(int l = 0; l+d < n; l++){
			int r = l+d;
			dp[l][r] = LINF;
			for(int k = opt[l][r-1]; k <= opt[l+1][r]; k++){
				ll cur = dp[l][k] + dp[k+1][r] + C(l, r);
				if(cur < dp[l][r]){
					dp[l][r] = cur;
					opt[l][r] = k;
				}
			}
		}
	}
}
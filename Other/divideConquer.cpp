//Divide conquer DP
//dp[i][j] = min(dp[k][j-1] + C(k+1, i))

void divideConquer(int l, int r, int optl, int optr){
	if(l > r) return;
	int mid = (l + r)/2, opt = optl;
	new_dp[mid] = INF;
	for(int k = optl; k <= min(optr, mid); k++){
		ll cur = old_dp[k] + C(k+1, mid);
		if(cur < new_dp[mid]){
			new_dp[mid] = cur;
			opt = k;
		}
	}
	divideConquer(l, mid-1, optl, opt);
	divideConquer(mid+1, r, opt, optr);
}
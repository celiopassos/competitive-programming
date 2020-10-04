//interpolates (x1, y1), ... (xn, yn) and evaluate p(x)
//where xi = i
//O(n)
int lagrangeInterpolation(const vi &v, int x){
	int n = v.size();
	vi inv(n+1, 1), inv_fact(n+1, 1), pref(n+2, 1), suff(n+2, 1);
	for(int i = 2; i <= n; i++){
		inv[i] = MOD - (MOD/i)*(ll)inv[MOD%i] % MOD;
		inv_fact[i] = inv_fact[i-1] *(ll) inv[i] % MOD; 
	}
	for(int i = 1; i <= n; i++) pref[i] = (pref[i-1] *(ll) (x - i)) % MOD;
	for(int i = n; i >= 1; i--) suff[i] = (suff[i+1] *(ll) (x - i)) % MOD;
	int res = 0;
	for(int i = 1; i <= n; i++){
		int cur = (pref[i-1] *(ll) suff[i+1]) % MOD;
		cur = cur *(ll)v[i-1] % MOD;
		cur = cur *(ll)inv_fact[n-i] % MOD; 
		cur = cur *(ll)inv_fact[i-1] % MOD; 
		if((n-i) & 1) cur = MOD - cur;
		res = (res + cur)% MOD;
	}
	return res;
}
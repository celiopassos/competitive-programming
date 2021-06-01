struct HASH{
	size_t operator()(const pair<ll,int>&x)const{
		return hash<long long>()(((long long)x.first)^(((long long)x.second)<<40));
	}
};

const int MAX_SIEVED = 1e7;
unordered_map<pair<ll, int>, ll, HASH> mp_phi;
unordered_map<ll, ll> mp_pi;
vector<int> primes;//remember to fill this vector with primes less than MAX_SIEVED

ll phi(ll x, int a){
	if(mp_phi.count({x, a}))return mp_phi[{x, a}];
	if(a == 1) return (x + 1)/2;
	return mp_phi[{x, a}] = phi(x, a-1) - phi(x / primes[a-1], a-1);
}

ll pi(ll x){//Prime counting function O(n^2/3)
	if(mp_pi.count(x)) return mp_pi[x];
	if(x < MAX_SIEVED)
		return mp_pi[x] = (lower_bound(primes.begin(), primes.end(), x+1) - primes.begin());
	ll a = pi((int)pow(x, 1.0/4));
	ll b = pi((int)pow(x, 1.0/2));
	ll c = pi((int)pow(x, 1.0/3));
	ll ans = phi(x,a) + (b+a-2) * (b-a+1)/2;
	for(int i = a+1; i <= b; i++){
		ll w = x/primes[i-1];
		ll b_i = pi((ll)sqrt(w));
		ans -= pi(w);
		for(int j = i; i <= c && j <= b_i; j++)
			ans -= pi(w / primes[j-1]) - j + 1;
	}
	return mp_pi[x] = ans;
}
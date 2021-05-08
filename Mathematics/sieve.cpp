auto sieve(int N) {
    vector<int> lp(N + 1, 0), pr;
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) pr.push_back(lp[i] = i);
        for (auto p : pr) {
            if (p > lp[i] || i * p > N) break;
            lp[i * p] = p;
        }
    }
    return pair(lp, pr);
}

//Euler totient of numbers from 0 to MAX-1
//O(n)
bool composite[MAX];
int phi[MAX];
vector<int> primes;

void sieve(){
	phi[1] = 1;
	for(int i = 2; i < MAX; i++){
		if(!composite[i]){
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int j = 0; j < (int)primes.size() && i * (ll)primes[j] < MAX; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0){ 
				phi[i * primes[j]] = phi[i] * primes[j];
				break;
			}
			else{
				phi[i * primes[j]] = phi[i] * phi[primes[j]];
			}
		}
	}
}


//Compute mobius function of numbers from 0 to MAX-1
//O(n)
bool composite[MAX];
int M[MAX];
vector<int> primes;

void sieve(){
	M[1] = 1;
	for(int i = 2; i < MAX; i++){
		if(!composite[i]){
			primes.push_back(i);
			M[i] = -1;
		}
		for (int j = 0; j < (int)primes.size() && i * (ll)primes[j] < MAX; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0){ 
				M[i * primes[j]] = 0;
				break;
			}
			else{
				M[i * primes[j]] = M[i] * M[primes[j]];
			}
		}
	}
}


//segmented sieve
vector<int> primes;

void sieve(int n) {
    ll S = sqrt(n)+1;
    vector<bool> is_prime(S, true);
	for (int i = 2; i < S; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j < S; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> p1;
	for (ll k = 1; k * S <= n; k++) {
        fill(is_prime.begin(), is_prime.end(), true);
        ll start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            ll j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                is_prime[j] = false;
        }
        for (int i = 0; i < S && start + i <= n; i++)
            if (is_prime[i]) p1.push_back(start + i);
    }
	for(auto x: p1)primes.push_back(x);
}
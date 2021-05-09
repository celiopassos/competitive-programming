//MillerRabin
//Complexity O(log n)
//If n is 32bit use just the first four values of a

ll exp(ll a, ll n, ll mod) {
    ll ans = 1;
    a %= mod;
    while(n) {
        if (n & 1) ans = a *(__int128) ans % mod;
        a = a *(__int128) a % mod;
        n /= 2;
    }
    return ans;
}

//return 1 if n is composite and 0 if it's probably prime
int composite(ll n, ll a, ll d, int sz) {
    ll x = exp(a, d, n);
    if (x == 1 || x == n - 1)
        return 0;
    for (int r = 1; r < sz; r++) {
        x = x *(__int128) x % n;
        if (x == n - 1)
            return 0;
    }
    return 1;
};

//returns 1 if n is prime, else returns 0.
int MillerRabin(ll n) { 
    if (n < 2)return 0;
    int sz = 0;
    ll d = n - 1;
    while ((d & 1) == 0){
        d >>= 1;
        sz++;
    }
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return 1;
        if (composite(n, a, d, sz)) return 0;
    }
    return 1;
}
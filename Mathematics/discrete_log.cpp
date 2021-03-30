// assumes a and mod are coprime
// return -1 if not found
// O(sqrt(mod)log(mod))

ll discrete_log(ll a, ll b, ll mod) {
    a %= mod, b %= mod;

    ll n = (ll)sqrt(mod) + 1;
    ll apow = 1;

    for (int i = 0; i < n; ++i) (apow *= a) %= mod;

    vector<pair<ll, ll>> values;

    for (ll q = 0, cur = b; q <= n; ++q) {
        values.emplace_back(cur, q);
        (cur *= a) %= mod;
    }

    sort(all(values));

    for (ll p = 1, cur = 1; p <= n; ++p) {
        (cur *= apow) %= mod;
        auto iter = lower_bound(all(values), pair(cur, 0LL));
        if (iter != end(values) && iter->first == cur) {
            ll ans = n * p - iter->second;
            return ans;
        }
    }

    return -1;
}

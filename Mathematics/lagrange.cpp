// Finds p(x), given that p is the unique polynomial of degree n - 1
// such that p(i) = y[i], for i = 0, ..., n - 1.
ll interpolate(const vector<ll>& y, ll x, ll mod) {
    int n = (int)size(y);
    vector<ll> inv(n, 1), finv(n, 1);
    for (int i = 2; i < n; ++i) {
        inv[i] = -(mod / i) * inv[mod % i] % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
    vector<ll> prefix(n, 1), suffix(n, 1);
    for (int i = 0; i + 1 < n; ++i) pref[i + 1] = pref[i] * (x - i) % mod;
    for (int i = n - 1; i > 0; --i) suff[i - 1] = suff[i] * (x - i) % mod;
    ll res = 0LL;
    for (int i = 0, sgn = (n % 2 ? +1 : -1); i < n; ++i, sgn *= -1) {
        ll coef = sgn * prefix[i] * suffix[i] % mod * finv[i] % mod * finv[n - 1 - i] % mod;
        res = (res + y[i] * coef) %= mod;
    }
    return (res + mod) % mod;
}
// N = maximum degree + 1
// T = modular int class
template<typename T, int N>
struct Interpolator {
    T f[N], finv[N];
    Interpolator() {
        f[0] = finv[0] = 1;
        for (int x = 1; x < N; ++x) f[x] = x * f[x - 1], finv[x] = 1 / f[x];
    }
    T interpolate(const vector<T>& y, T x) {
        static T pref[N], suff[N];
        int n = (int)size(y);
        pref[0] = suff[n - 1] = 1;
        for (int i = 0; i + 1 < n; ++i) pref[i + 1] = pref[i] * (x - i);
        for (int i = n - 1; i > 0; --i) suff[i - 1] = suff[i] * (x - i);
        T res = 0;
        for (int i = 0, sgn = (n % 2 ? +1 : -1); i < n; ++i, sgn *= -1) {
            res += y[i] * sgn * pref[i] * suff[i] * finv[i] * finv[n - 1 - i];
        }
        return res;
    }
};

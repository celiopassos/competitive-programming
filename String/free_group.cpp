const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(FIXED_RANDOM);

uniform_int_distribution<ll> unif(1e5, 1e6);

ll modpow(ll x, ll p, ll mod) {
    ll res = 1;
    for (; p; p >>= 1, (x *= x) %= mod) if (p & 1) (res *= x) %= mod;
    return res;
}

template<typename T, typename Op>
T templatepow(T x, T Id, ll p, Op&& op) {
    T res = Id;
    while (p > 0) {
        if (p & 1) res = op(res, x);
        p >>= 1, x = op(x, x);
    }
    return res;
}

template<ll mod>
struct FreeGroup {
    inline static const ll base = unif(rng), inv_base = modpow(base, mod - 2, mod);

    ll shift, inv_shift, hash;
    FreeGroup(ll shift, ll inv_shift, ll hash) : shift(shift), inv_shift(inv_shift), hash(hash) { }

    FreeGroup() : shift(1), inv_shift(1), hash(0) { }
    FreeGroup(ll c) : shift(base), inv_shift(inv_base), hash(c + 1) { }
    FreeGroup(const string& s) : FreeGroup() {
        for (auto c : s) *this += FreeGroup(c);
    }

    FreeGroup& operator+=(const FreeGroup& rhs) {
        shift = shift * rhs.shift % mod;
        inv_shift = inv_shift * rhs.inv_shift % mod;
        hash = (rhs.shift * hash + rhs.hash) % mod;
        return *this;
    }
    FreeGroup operator-=(const FreeGroup& rhs) { *this += (-rhs); }
    FreeGroup operator+(const FreeGroup& rhs) const { return FreeGroup(*this) += rhs; }
    FreeGroup operator-(const FreeGroup& rhs) const { return FreeGroup(*this) -= rhs; }
    FreeGroup operator-() const {
        return FreeGroup(inv_shift, shift, (mod - inv_shift * hash % mod) % mod);
    }
    FreeGroup power(ll p) const {
        FreeGroup x = *this;
        if (p < 0) p *= -1, x = -x;
        return templatepow(x, FreeGroup(), p, plus<FreeGroup>());
    }
    bool operator<(const FreeGroup& rhs) const { return pair(shift, hash) < pair(rhs.shift, rhs.hash); }
    bool operator==(const FreeGroup& rhs) const { return shift == rhs.shift && hash == rhs.hash; }
    bool operator!=(const FreeGroup& rhs) const { return not *this == rhs; }
};

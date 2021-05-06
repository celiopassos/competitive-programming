const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(FIXED_RANDOM);

ll modpow(ll x, ll p, ll mod) {
    ll res = 1;
    for (; p; p >>= 1, (x *= x) %= mod) if (p & 1) (res *= x) %= mod;
    return res;
}

// Beware that FreeGroup() is the identity, NOT FreeGroup(0)!
// Not commutative (of course), so pay attention when querying substrings via prefix sums.

template<ll mod>
struct FreeGroup {
    inline static const ll base = uniform_int_distribution<ll>(2, mod - 1)(rng), inv_base = modpow(base, mod - 2, mod);

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
    FreeGroup& operator-=(const FreeGroup& rhs) { return *this += (-rhs); }
    FreeGroup operator+(const FreeGroup& rhs) const { return FreeGroup(*this) += rhs; }
    FreeGroup operator-(const FreeGroup& rhs) const { return FreeGroup(*this) -= rhs; }
    FreeGroup operator+() const { return *this; }
    FreeGroup operator-() const {
        return FreeGroup(inv_shift, shift, (mod - inv_shift * hash % mod) % mod);
    }
    FreeGroup power(ll p) const {
        FreeGroup x = *this;
        if (p < 0) p *= -1, x = -x;
        FreeGroup res;
        while (p) {
            if (p & 1) res = res + x;
            x += x, p >>= 1;
        }
        return res;
    }
    bool operator<(const FreeGroup& rhs) const { return pair(shift, hash) < pair(rhs.shift, rhs.hash); }
    bool operator==(const FreeGroup& rhs) const { return shift == rhs.shift && hash == rhs.hash; }
    bool operator!=(const FreeGroup& rhs) const { return not (*this == rhs); }
};

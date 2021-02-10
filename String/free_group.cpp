const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(FIXED_RANDOM);

uniform_int_distribution<ll> unif(100, 1e6);

ll modpow(ll x, ll p, ll mod)
{
    ll res = 1;
    for (; p; p >>= 1, (x *= x) %= mod) if (p & 1) (res *= x) %= mod;
    return res;
}

template<ll mod>
struct FreeGroup
{
    inline static const ll base = unif(rng), inv_base = modpow(base, mod - 2, mod);

    ll shift, inv_shift, hash;
    FreeGroup(ll shift, ll inv_shift, ll hash) : shift(shift), inv_shift(inv_shift), hash(hash) { }

    FreeGroup() : shift(1), inv_shift(1), hash(0) { }
    FreeGroup(ll c) : shift(base), inv_shift(inv_base), hash(c) { }
    FreeGroup(const string& s) : FreeGroup()
    {
        for (auto c : s) *this = *this + FreeGroup(c);
    }

    FreeGroup operator+(const FreeGroup& rhs) const
    {
        ll newshift = shift * rhs.shift % mod;
        ll newinvshit = inv_shift * rhs.inv_shift % mod;
        ll newhash = (rhs.shift * hash + rhs.hash) % mod;
        return FreeGroup(newshift, newinvshit, newhash);
    }
    FreeGroup operator-(const FreeGroup& rhs) const
    {
        return *this + (-rhs);
    }
    FreeGroup operator-() const
    {
        return FreeGroup(inv_shift, shift, (mod - inv_shift * hash % mod) % mod);
    }
    bool operator<(const FreeGroup& rhs) const { return pair(shift, hash) < pair(rhs.shift, rhs.hash); }
    bool operator==(const FreeGroup& rhs) const { return shift == rhs.shift && hash == rhs.hash; }
};

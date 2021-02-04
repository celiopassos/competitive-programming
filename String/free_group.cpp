template<ll mod, typename T=int>
struct FreeGroup
{
    static ll base;
    ll shift, hash;
    Hash() : shift(1), hash(0) { }
    Hash(ll shift, ll hash) : shift(shift), hash(hash) { }
    Hash(int c) : shift(base), hash(c) { }
    Hash operator+(const Hash& rhs) const
    {
        return Hash(shift * rhs.shift % mod, (rhs.shift * hash + rhs.hash) % mod);
    }
    Hash operator-() const
    {
        ll inv_shift = modpow(shift, mod - 2, mod);
        return Hash(inv_shift, (mod - inv_shift * hash % mod) % mod);
    }
    bool operator<(const Hash& rhs) const { return pair(shift, hash) < pair(rhs.shift, rhs.hash); }
    bool operator==(const Hash& rhs) const { return shift == rhs.shift && hash == rhs.hash; }
};

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const ll L = numeric_limits<char>::max() + 100LL, R = 1000000LL;
uniform_int_distribution<ll> random_base(L, R);

template<ll mod>
struct StringHash
{
    inline static const ll base = random_base(rng) | 1;
    inline static vector<ll> power;

    static void extend(int n)
    {
        int m = size(power);
        if (m >= n) return;
        power.resize(n, 1LL);
        for (int i = max(m, 1); i < n; ++i) power[i] = power[i - 1] * base % mod;
    }

    vector<ll> h;

    StringHash(const string& s) : h(size(s))
    {
        extend(size(s));
        h[0] = s[0] + 1;
        for (int i = 1; i < size(s); ++i) h[i] = (base * h[i - 1] + s[i] + 1) % mod;
    }
    ll query(int i, int j) const
    {
        if (i == 0) return h[j];
        return (h[j] + (mod - (h[i - 1] * power[j - i + 1]) % mod)) % mod;
    }
    ll concat(ll prefix, int i, int j) const
    {
        return (prefix * power[j - i + 1] % mod + query(i, j)) % mod;
    }
};

struct BigHash
{
    static constexpr ll mod1 = 1000000021LL, mod2 = 1000000033LL, mod3 = 1000000087LL;

    const StringHash<mod1> hash1;
    const StringHash<mod2> hash2;
    const StringHash<mod3> hash3;

    BigHash(const string& s) : hash1(s), hash2(s), hash3(s) {}
    auto query(int i, int j) const
    {
        return tuple(hash1.query(i, j), hash2.query(i, j), hash3.query(i, j));
    }
    auto concat(auto prefix, int i, int j) const
    {
        auto [prefix1, prefix2, prefix3] = prefix;
        return tuple(
            hash1.concat(prefix1, i, j),
            hash2.concat(prefix2, i, j),
            hash3.concat(prefix3, i, j)
        );
    }
};

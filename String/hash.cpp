#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<ll MOD, ll P>
class StringHash
{
private:
    vector<ll> power, h;
public:
    StringHash(const string& s)
    {
        const int n = size(s);
        power.assign(n, 1LL);
        h.assign(n, 0LL); h[0] = s[0] + 1;
        for (int i = 1; i < n; power[i] = (power[i - 1] * P) % MOD, ++i)
            h[i] = (P * h[i - 1] + s[i] + 1) % MOD;
    }
    ll query(int i, int j) const
    {
        if (i == 0) return h[j];
        return (h[j] + (MOD - (h[i - 1] * power[j - i + 1]) % MOD)) % MOD;
    }
    ll concat(ll prefix, int i, int j) const
    {
        return (prefix * power[j - i + 1] % MOD + query(i, j)) % MOD;
    }
};

class BigHash
{
private:
    static constexpr ll MOD1 = 998244353, MOD2 = 1e9 + 7, MOD3 = 1e9 + 9;
    static constexpr ll P1 = 263, P2 = 271, P3 = 353;
    const StringHash<MOD1, P1> hash1;
    const StringHash<MOD2, P2> hash2;
    const StringHash<MOD3, P3> hash3;
public:
    BigHash(const string& s) : hash1(s), hash2(s), hash3(s) {}
    auto query(int i, int j) const
    {
        return tuple(hash1.query(i, j), hash2.query(i, j), hash3.query(i, j));
    }
    template<typename... Args>
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

int main()
{ _
    exit(0);
}


#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
class StringHash
{
private:
    vector<ll> power, h;
public:
    StringHash(const string& s)
    {
        const int n = sz(s);
        power.assign(n, 1LL);
        h.assign(n, 0LL); h[0] = s[0] + 1;
        for (int i = 1; i < n; power[i] = (power[i - 1] * P) % MOD, ++i)
            h[i] = (P * h[i - 1] + s[i] + 1) % MOD;
    }
    ll query(int i, int j) const
    {
        if (i == 0) return h[j];
        return (h[j] + (MOD - (h[i - 1] * power[j - (i - 1)]) % MOD)) % MOD;
    }
};

#define SEED ((((__TIME__[7] * 1337) ^ ((__TIME__[6] * 222) << 3)) + (__TIME__[8] + 44)) | 1)

class BigHash
{
private:
    static constexpr ll MOD1 = 998244353, MOD2 = 1e9 + 7, MOD3 = 1e9 + 9;
    static constexpr ll P1 = 31, P2 = 37, P3 = (53 + (SEED % 447)) | 1;
    const StringHash<MOD1, P1> hash1;
    const StringHash<MOD2, P2> hash2;
    const StringHash<MOD3, P3> hash3;
public:
    BigHash(const string& s) : hash1(s), hash2(s), hash3(s) {}
    auto query(int i, int j) const
    {
        return tuple{ hash1.query(i, j), hash2.query(i, j), hash3.query(i, j) };
    }
};

int main()
{ _
    exit(0);
}


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

// xz

template<ll MOD, ll P>
class StringHash
{
private:
    vector<ll> power, h;
public:
    StringHash(const string& s)
    {
        const int n = sz(s);
        power.assign(n, 1LL);
        h.assign(n, 0LL); h[0] = s[0];
        for (int i = 1; i < n; power[i] = (power[i - 1] * P) % MOD, ++i)
            h[i] = (P * h[i - 1] + s[i]) % MOD;
    }
    ll query(int i, int j) const
    {
        if (i == 0) return h[j];
        return (h[j] + (MOD - (h[i - 1] * power[j - (i - 1)]) % MOD)) % MOD;
    }
};

int main()
{ _
    exit(0);
}


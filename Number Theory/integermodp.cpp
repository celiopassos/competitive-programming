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

ll power(ll x, int p, ll MOD)
{
    ll res = 1;
    while (p)
    {
        if (p & 1) res = (res * x) % MOD;
        p >>= 1;
        x = (x * x) % MOD;
    }
    return res;
}

template<ll MOD>
struct IntegerModp
{
    ll x;
    IntegerModp(ll x = 0) : x(x) {};
    IntegerModp inv() const { assert(x != 0); return ll(power(x, MOD - 2, MOD)); }
    IntegerModp& operator+=(const IntegerModp& rhs) { x = (x + rhs.x) % MOD; return *this; }
    IntegerModp& operator-=(const IntegerModp& rhs) { x = (x + MOD - rhs.x) % MOD; return *this; }
    IntegerModp& operator*=(const IntegerModp& rhs) { x = (x * rhs.x) % MOD; return *this; }
    IntegerModp& operator/=(const IntegerModp& rhs) { return *this *= rhs.inv(); }
    IntegerModp operator+(const IntegerModp& rhs) const { return IntegerModp(*this) += rhs; }
    IntegerModp operator-(const IntegerModp& rhs) const { return IntegerModp(*this) -= rhs; }
    IntegerModp operator*(const IntegerModp& rhs) const { return IntegerModp(*this) *= rhs; }
    IntegerModp operator/(const IntegerModp& rhs) const { return IntegerModp(*this) /= rhs; }
    bool operator==(const IntegerModp& rhs) const { return x == rhs.x; }
    bool operator<(const IntegerModp& rhs) const { return x < rhs.x; }
};

int main()
{ _
    exit(0);
}


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

ll modpow(ll x, ll p, ll mod)
{
    x %= mod, (p %= mod - 1) < 0 ? p += mod - 1 : 0LL;
    ll res = 1LL;
    while (p > 0)
    {
        if (p & 1) res = res * x % mod;
        x = x * x % mod, p >>= 1;
    }
    return res;
}

template<int mod, bool safe = false>
struct Mint
{
    int x;
    Mint(ll x = 0) : x(int((x %= mod) < 0 ? x + mod : x)) {};
    Mint inv() const
    {
        if (safe) assert(x != 0);
        return Mint(modpow(x, mod - 2, mod));
    }
    Mint& operator+=(const Mint& rhs) { if ((x += rhs.x) >= mod) x -= mod; return *this; }
    Mint& operator-=(const Mint& rhs) { return *this += mod - rhs.x; }
    Mint& operator*=(const Mint& rhs) { x = int((1LL * x * rhs.x) % mod); return *this; }
    Mint& operator/=(const Mint& rhs) { return *this *= rhs.inv(); }
    Mint operator+(const Mint& rhs) const { return Mint(*this) += rhs; }
    Mint operator-(const Mint& rhs) const { return Mint(*this) -= rhs; }
    Mint operator*(const Mint& rhs) const { return Mint(*this) *= rhs; }
    Mint operator/(const Mint& rhs) const { return Mint(*this) /= rhs; }
    Mint power(ll p) const
    {
        if (safe) assert(p >= 0LL || x != 0);
        return Mint(modpow(x, p, mod));
    }
    bool operator==(const Mint& rhs) const { return x == rhs.x; }
    bool operator<(const Mint& rhs) const { return x < rhs.x; }
    friend ostream& operator<<(ostream& out, const Mint& a) { out << a.x; return out; }
    friend istream& operator>>(istream& in, Mint& a)
    {
        ll x; in >> x;
        a = Mint(x);
        return in;
    }
};

int main()
{ _
    exit(0);
}

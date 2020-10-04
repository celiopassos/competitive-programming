#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename T>
T power(T x, int p)
{
    T res = 1;
    while (p)
    {
        if (p & 1) res *= x;
        p >>= 1;
        x *= x;
    }
    return res;
}

template<ll MOD>
struct Mint
{
    ll x;
    Mint(ll x = 0) : x(x % MOD) {};
    Mint inv() const { assert(x != 0); return power(*this, MOD - 2); }
    Mint& operator+=(const Mint& rhs) { x = (x + rhs.x) % MOD; return *this; }
    Mint& operator-=(const Mint& rhs) { x = (x + MOD - rhs.x) % MOD; return *this; }
    Mint& operator*=(const Mint& rhs) { x = (x * rhs.x) % MOD; return *this; }
    Mint& operator/=(const Mint& rhs) { return *this *= rhs.inv(); }
    Mint operator+(const Mint& rhs) const { return Mint(*this) += rhs; }
    Mint operator-(const Mint& rhs) const { return Mint(*this) -= rhs; }
    Mint operator*(const Mint& rhs) const { return Mint(*this) *= rhs; }
    Mint operator/(const Mint& rhs) const { return Mint(*this) /= rhs; }
    bool operator==(const Mint& rhs) const { return x == rhs.x; }
    bool operator<(const Mint& rhs) const { return x < rhs.x; }
};

int main()
{ _
    exit(0);
}


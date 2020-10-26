#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename T> struct StringHash
{
private:
    static const T B;
    const int n;
    vector<T> p, h;
    template<typename... Args> T concat() { return T(0); }
public:
    StringHash(const string& s) : n(size(s)), p(n, T(1)), h(n, T(0))
    {
        const int n = size(s);
        h[0] = T(s[0] + 1);
        for (int i = 1; i < n; p[i] = p[i - 1] * B, ++i)
            h[i] = (B * h[i - 1] + T(s[i] + 1));
    }
    T query(int i, int j) const
    {
        return i > 0 ? h[j] - h[i - 1] * p[j - i + 1] : h[j];
    }
    template<typename... Args> T concat(int i, int j, Args... args) // reverse order
    {
        return query(i, j) + p[j - i + 1] * concat(args...);
    }
};

constexpr int MODs[] = { 998244353, 1000000007, 1000000009 };
constexpr int base[] = { 263, 271, 353 };

// using T = Pointwise<Mint<MODs[0]>, Mint<MODs[1]>, Mint<MODs[2]>>;
// using H = StringHash<T>;

// template<>
// const T H::B(base[0], base[1], base[2]);

int main()
{ _
    exit(0);
}


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

ll hilbert(int x, int y, int N)
{
    ll d = 0;
    for (int s = N >> 1; s > 0; s >>= 1)
    {
        int rx = (x & s) > 0, ry = (y & s) > 0;
        d += 1LL * s * s * ((3 * rx) ^ ry);
        if (ry == 0)
        {
            if (rx == 1) x = N - 1 - x, y = N - 1 - y;
            swap(x, y);
        }
    }
    return d;
}

int logceil(int n)
{
    return __builtin_clz(1) - __builtin_clz(n) + !!(n & -n);
}

void mo(const auto& queries, auto& eval, auto& remove, auto& insert, int n)
{
    const int q = size(queries), N = 1 << logceil(n);

    vector<int> Z(q, 0); iota(all(Z), 0);

    vector<ll> h(q, 0LL);

    for (int z = 0; z < q; ++z)
    {
        auto [l, r] = queries[z];
        h[z] = hilbert(l, r, N);
    }

    sort(all(Z), [&h](int z, int w) { return h[z] < h[w]; });

    int lcur = 0, rcur = 0; insert(0);

    auto update = [&](int l, int r)
    {
        while (l < lcur) insert(--lcur);
        while (rcur < r) insert(++rcur);
        while (lcur < l) remove(lcur++);
        while (r < rcur) remove(rcur--);
    };

    for (auto z : Z)
    {
        auto [l, r] = queries[z];
        update(l, r), eval(z);
    }
}

int main()
{ _
    exit(0);
}

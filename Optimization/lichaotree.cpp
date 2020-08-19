#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

template<typename T, typename F = T>
struct Hull
{
    vector<T> a;
    int N;
    const T infinity = T(LINF); // may wanna change if T is float
    typedef complex<T> point;
    vector<point> line;
    Hull(const vector<T>& domain) : a(domain)
    {
        sort(all(a)), a.erase(unique(all(a)), a.end());
        int n = sz(a); N = 1 << (32 - __builtin_clz(n));
        a.resize(N), iota(a.begin() + n, a.end(), a[n - 1] + 1);
        line.assign(2 * N, point(0, infinity));
    }
    F dot(point p, point q) { return (conj(p) * q).real(); }
    F f(point p, int i) { return dot(p, {a[i], 1}); }
    void update(point nw)
    {
        for (int p = 1, l = 0, r = N - 1; p < 2 * N;)
        {
            int m = (l + r) / 2;
            bool left = f(nw, l) < f(line[p], l);
            bool mid = f(nw, m) < f(line[p], m);
            if (mid) swap(line[p], nw);
            if (left != mid)
                r = m, p = p << 1;
            else
                l = m + 1, p = p << 1 | 1;
        }
    }
    F get(T x)
    {
        int i = distance(a.begin(), lower_bound(all(a), x)), p = N + i;
        assert(a[i] == x); // remove if T is float
        F res = f(line[p], i);
        while (p) res = min(res, f(line[p >>= 1], i));
        return res;
    }
};

int main()
{ _
    exit(0);
}


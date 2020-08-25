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

template<typename T>
class BIT
{
private:
    inline T combine(T x, T y) { return x + y; }
    inline T inv(T x) { return -x; }

    inline int down(int p) { return (p & (p + 1)) - 1; }
    inline int up(int p) { return p | (p + 1); }

    const int n; const T id;
    vector<T> ft;
    T query(int p)
    {
        T res = id;
        for (int i = p; i >= 0; i = down(i))
            res = combine(ft[i], res);
        return res;
    }
public:
    BIT(vector<T> a, T id) : id(id), n(sz(a))
    {
        ft = a;
        for (int i = 1; i < n; ++i)
            ft[i] = combine(ft[i - 1], ft[i]);
        for (int i = n - 1; i > 0; --i)
            if (down(i) >= 0) ft[i] = combine(inv(ft[down(i)]), ft[i]);
    }
    T query(int l, int r)
    {
        if (l == 0) return query(r);
        return combine(inv(query(l - 1)), query(r));
    }
    void update(int p, T value)
    {
        for (int i = p; i < n; i = up(i)) ft[i] = combine(ft[i], value);
    }
};

int main()
{ _
    exit(0);
}


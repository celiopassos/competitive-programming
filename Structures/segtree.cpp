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
class SegmentTree
{
private:
    const int n;
    vector<T> st;
    const T id;
    T op(T l, T r) { return l + r; }
    void build()
    {
        for (int i = n - 1; i > 0; --i)
            st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
public:
    SegmentTree(const vector<T>& a, T id) : n(sz(a)), id(id)
    {
        st.assign(2 * n, id);
        for (int i = 0; i < n; ++i) st[n + i] = a[i];
        build();
    }
    void modify(int p, T value)
    {
        for (st[p += n] = value; p > 1; p >>= 1)
            st[p >> 1] = op(st[p & ~1], st[p | 1]);
    }
    T query(int l, int r) // inclusive
    {
        T resl = id, resr = id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) resl = op(resl, st[l++]);
            if (r & 1) resr = op(st[--r], resr);
        }
        return op(resl, resr);
    }
};

int main()
{ _
    exit(0);
}


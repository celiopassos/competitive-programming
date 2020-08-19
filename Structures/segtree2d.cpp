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
class SegmentTree2D
{
private:
    const int n, m;
    vector<vector<T>> st;
    const T id;
    T op(T l, T r) { return l + r; }
    void build()
    {
        for (int i = 0; i < n; ++i)
            for (int j = m - 1; j > 0; --j)
                st[n + i][j] = op(st[n + i][j << 1], st[n + i][j << 1 | 1]);
        for (int i = n - 1; i > 0; --i)
            for (int j = m - 1; j > 0; --j)
                st[i][j] = op(st[i << 1][j], st[i << 1 | 1][j]);
    }
public:
    SegmentTree2D(const vector<vector<T>>& a, T id) : n(sz(a)), m(sz(a[0])), id(id)
    {
        st.assign(2 * n, vector<T>(2 * m, id));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                st[n + i][m + j] = a[i][j];
        build();
    }
    void modify(int p, int q, T value)
    {
        st[p + n][q + m] = value;
        for (int s = q + m; s >>= 1;)
            st[p + n][s] = op(st[p + n][s << 1], st[p + n][s << 1 | 1]);
        for (int r = p + n; r >>= 1;)
            for (int s = q + m; s; s >>= 1)
                st[r][s] = op(st[r << 1][s], st[r << 1 | 1][s]);
    }
    T query(int l, int r, int x, int y)
    {
        T res = id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            int I[2] = { -1, -1 };
            if (l & 1) I[0] = l++;
            if (r & 1) I[1] = --r;
            for (int t = 0; t < 2; ++t)
            {
                int p = I[t]; if (p == -1) continue;
                for (int z = x + m, w = y + m + 1; z < w; z >>= 1, w >>= 1)
                {
                    if (z & 1) res = op(res, st[p][z++]);
                    if (w & 1) res = op(res, st[p][--w]);
                }
            }
        }
        return res;
    }
};

int main()
{ _
    exit(0);
}


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

template<typename T>
class SegmentTree2D
{
private:
    const int n, m; const T Tid;
    vector<vector<T>> st;
    T combine(T l, T r) { return l + r; }
    void build()
    {
        for (int i = 0; i < n; ++i)
            for (int j = m - 1; j > 0; --j)
                st[n + i][j] = combine(st[n + i][j << 1], st[n + i][j << 1 | 1]);
        for (int i = n - 1; i > 0; --i)
            for (int j = m - 1; j > 0; --j)
                st[i][j] = combine(st[i << 1][j], st[i << 1 | 1][j]);
    }
    T inner_query(int p, int x, int y)
    {
        T res = Tid;
        for (x += m, y += m + 1; x < y; x >>= 1, y >>= 1)
        {
            if (x & 1) res = combine(res, st[p][x++]);
            if (y & 1) res = combine(res, st[p][--y]);
        }
        return res;
    }
public:
    SegmentTree2D(const vector<vector<T>>& a, T Tid) : n(sz(a)), m(sz(a[0])), Tid(Tid)
    {
        st.assign(2 * n, vector<T>(2 * m, Tid));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                st[n + i][m + j] = a[i][j];
        build();
    }
    void modify(int p, int q, T value)
    {
        st[p + n][q + m] = value;
        for (int s = q + m; s >>= 1;)
            st[p + n][s] = combine(st[p + n][s << 1], st[p + n][s << 1 | 1]);
        for (int r = p + n; r >>= 1;)
            for (int s = q + m; s; s >>= 1)
                st[r][s] = combine(st[r << 1][s], st[r << 1 | 1][s]);
    }
    T query(int l, int r, int x, int y)
    {
        T res = Tid;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) res = combine(res, inner_query(l++, x, y));
            if (r & 1) res = combine(res, inner_query(--r, x, y));
        }
        return res;
    }
};

int main()
{ _
    exit(0);
}


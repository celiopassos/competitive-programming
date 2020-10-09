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

template<typename T>
struct SegmentTree
{
private:
    const int n;
    const T Tid;
    const function<T(T, T)> op;
    vector<T> st;
public:
    SegmentTree(int n, T Tid, auto op) : n(n), Tid(Tid), op(op) { st.assign(2 * n, Tid); }
    SegmentTree(const vector<T>& a, T Tid, auto op) : SegmentTree(size(a), Tid, op)
    {
        for (int i = 0; i < n; ++i) st[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
    void modify(int p, T value)
    {
        for (st[p += n] = value; p > 1; p >>= 1)
            st[p >> 1] = op(st[p & ~1], st[p | 1]);
    }
    T query(int l, int r)
    {
        T resl = Tid, resr = Tid;
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


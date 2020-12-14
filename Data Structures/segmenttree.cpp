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

template<typename T>
struct M1
{
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static bool cmp(const T& x, const T& y) { return x < y; }
};

template<typename Monoid>
struct SegmentTree
{
private:
    using M = Monoid;
    using T = typename Monoid::Type;
    const int n;
    vector<T> st;
    int binary_search(int p, T prefix, T value)
    {
        while (p < n) if (T x = M::op(prefix, st[p <<= 1]); M::cmp(x, value))
            prefix = x, p |= 1;
        return p - n + M::cmp(M::op(prefix, st[p]), value);
    }
public:
    SegmentTree(int n) : n(n), st(2 * n, M::Id) { }
    SegmentTree(const vector<T>& a) : SegmentTree(size(a))
    {
        for (int i = 0; i < n; ++i) st[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            st[i] = M::op(st[i << 1], st[i << 1 | 1]);
    }
    void modify(int p, T value)
    {
        for (st[p += n] = value; p > 1; p >>= 1)
            st[p >> 1] = M::op(st[p & ~1], st[p | 1]);
    }
    T query(int l, int r)
    {
        T resl = M::Id, resr = M::Id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) resl = M::op(resl, st[l++]);
            if (r & 1) resr = M::op(st[--r], resr);
        }
        return M::op(resl, resr);
    }
    int lower_bound(T value) { return lower_bound(0, n - 1, value); }
    // first x in [a, b] with M::cmp(query(a, x), value) == false
    int lower_bound(int a, int b, T value)
    {
        static deque<int> deq;
        static stack<int> stk;

        for (int l = a + n, r = b + n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) deq.push_back(l++);
            if (r & 1) stk.push(--r);
        }

        while (not empty(stk)) deq.push_back(stk.top()), stk.pop();

        for (T prefix = M::Id; not empty(deq);)
        {
            int p = deq.front(); deq.pop_front();

            if (T x = M::op(prefix, st[p]); M::cmp(x, value)) prefix = x;
            else
            {
                deq.clear();
                return binary_search(p, prefix, value);
            }
        }

        return b + 1;
    }
};

int main()
{ _
    exit(0);
}

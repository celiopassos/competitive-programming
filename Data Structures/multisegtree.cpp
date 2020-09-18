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

// Only useful if the elements don't form a group.
// Otherwise, use BIT.

template<typename T, int... Args>
struct SegmentTree
{
    using ST = SegmentTree<T>;
    static const T id = T();
    static T combine(T x, T y) { return x + y; }
    static void update(ST& a, ST& b, ST& c, T)
    {
        a.value = combine(b.value, c.value);
    }
    T value = id;
    void modify(T value) { this->value = value; }
    T query() { return value; }
};

template<typename T, int N, int... Ns>
struct SegmentTree<T, N, Ns...>
{
    using ST = SegmentTree<T>;
    using CUR = SegmentTree<T, N, Ns...>;
    using NXT = SegmentTree<T, Ns...>;
    array<SegmentTree<T, Ns...>, 2 * N> st;
    template<typename... Args>
    static void update(CUR& a, CUR& b, CUR& c, int p, Args... args)
    {
        for (int r = p + N; r; r >>= 1)
            NXT::update(a.st[r], b.st[r], c.st[r], args...);
    }
    template<typename... Args>
    void modify(int p, Args... args)
    {
        st[p += N].modify(args...);
        while (p >>= 1) NXT::update(st[p], st[p << 1], st[p << 1 | 1], args...);
    }
    template<typename... Args>
    T query(int l, int r, Args... args)
    {
        T res = ST::id;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) res = ST::combine(res, st[l++].query(args...));
            if (r & 1) res = ST::combine(st[--r].query(args...), res);
        }
        return res;
    }
};

int main()
{ _
    exit(0);
}

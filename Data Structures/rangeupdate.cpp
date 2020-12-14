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
struct M3 // assignment
{
    using Type = T;
    inline const static T Id = INF;
    static T op(const T& x, const T& y)
    {
        return x == Id ? y : x;
    }
};

// updates are applied on the left
// delete push method if the monoid is commutative

template<typename Monoid>
struct RangeUpdate
{
private:
    using M = Monoid;
    using T = typename Monoid::Type;
    const int n, h;
    vector<T> st;
public:
    RangeUpdate(int n) : n(n), h(32 - __builtin_clz(n)), st(2 * n, M::Id) { }
    RangeUpdate(const vector<T>& init) : RangeUpdate(size(init))
    {
        copy(all(init), begin(st) + n);
    }
    T query(int p) const
    {
        T res = M::Id;
        for (p += n; p > 0; p >>= 1) res = M::op(st[p], res);
        return res;
    }
    void push(int p)
    {
        for (int s = h; s > 0; --s)
        {
            int q = p >> s;
            for (auto x : { q << 1, q << 1 | 1 }) st[x] = M::op(st[q], st[x]);
            st[q] = M::Id;
        }
    }
    void update(int l, int r, T value)
    {
        push(l + n), push(r + n);
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) { st[l] = M::op(value, st[l]); ++l; }
            if (r & 1) { --r; st[r] = M::op(value, st[r]); }
        }
    }
};

int main()
{ _
    exit(0);
}

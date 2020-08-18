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

template<typename X, typename T=X>
struct F1
{
    int L, R;
    X add;
    explicit F1(X add) : add(add) {}
    void apply_aggregate(T& old) const
    {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op) { add += op.add; }
    void operator=(const F1& op) { add = op.add; }
};

template<typename T, typename F>
class SegmentTree
{
private:
    const int n;
    vector<T> st; vector<F> lazy;
    const T Tid; const F Fid;
    inline int left(int p) const { return 2 * p + 1; }
    inline int right(int p) const { return 2 * p + 2; }
    T combine(const T& resl, const T& resr) const
    {
        return resl + resr;
    }
    void push(int p)
    {
        lazy[p].apply_aggregate(st[p]);
        if (lazy[p].L != lazy[p].R)
        {
            lazy[left(p)].compose(lazy[p]);
            lazy[right(p)].compose(lazy[p]);
        }
        lazy[p] = Fid;
    }
    void update(int p, int l, int r, int ql, int qr, F op)
    {
        push(p);
        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr) lazy[p].compose(op), push(p);
        else
        {
            int m = (l + r) / 2;
            update(left(p), l, m, ql, qr, op);
            update(right(p), m + 1, r, ql, qr, op);
            st[p] = combine(st[left(p)], st[right(p)]);
        }

    }
    T query(int p, int l, int r, int ql, int qr)
    {
        push(p);
        if (r < ql || qr < l) return Tid;
        if (ql <= l && r <= qr) return st[p];
        int m = (l + r) / 2;
        T resl = query(left(p), l, m, ql, qr);
        T resr = query(right(p), m + 1, r, ql, qr);
        return combine(resl, resr);
    }
public:
    SegmentTree(const vector<T>& a, T Tid, F Fid) : n(sz(a)), Tid(Tid), Fid(Fid)
    {
        st.assign(4 * n + 1, Tid);
        lazy.assign(4 * n + 1, Fid);
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            lazy[p].L = l, lazy[p].R = r;
            if (l == r) st[p] = a[l];
            else
            {
                int m = (l + r) / 2;
                build(left(p), l, m), build(right(p), m + 1, r);
                st[p] = combine(st[left(p)], st[right(p)]);
            }
        };
        build(0, 0, n - 1);
    }
    void update(int l, int r, F op) { update(0, 0, n - 1, l, r, op); }
    T query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

int main()
{ _
    exit(0);
}


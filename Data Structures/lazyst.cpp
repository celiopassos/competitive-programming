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

template<typename T, typename X = T>
struct F1
{
    static constexpr T Tid = T(0);
    static constexpr F1 Fid = F1(0);
    X add;
    constexpr explicit F1(X add) : add(add) {}
    void apply(T& old, int L, int R) const
    {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op, int L, int R)
    {
        add += op.add; (void)L, (void)R;
    }
    bool operator==(const F1& op) const { return add == op.add; }
    static T op(const T& lhs, const T& rhs)
    {
        return lhs + rhs;
    }
};

template<typename F>
class LazyST
{
private:
    const int n;
    using T = typename remove_const<decltype(F::Tid)>::type;
    vector<T> st;
    vector<F> lazy;
    int left(int p) const { return 2 * p + 1; }
    int right(int p) const { return 2 * p + 2; }
    void push(int p, int l, int r)
    {
        if (lazy[p] == F::Fid) return; // may wanna remove this...
        lazy[p].apply(st[p], l, r);
        if (l != r)
        {
            int m = l + (r - l) / 2;
            lazy[left(p)].compose(lazy[p], l, m);
            lazy[right(p)].compose(lazy[p], m + 1, r);
        }
        lazy[p] = F::Fid;
    }
    void update(int p, int l, int r, int ql, int qr, F op)
    {
        if (r < ql || qr < l) push(p, l, r);
        else if (ql <= l && r <= qr) { lazy[p].compose(op, l, r); push(p, l, r); }
        else
        {
            int m = l + (r - l) / 2;
            push(p, l, r);
            update(left(p), l, m, ql, qr, op);
            update(right(p), m + 1, r, ql, qr, op);
            st[p] = F::op(st[left(p)], st[right(p)]);
        }
    }
    T query(int p, int l, int r, int ql, int qr)
    {
        if (r < ql || qr < l) return F::Tid;
        push(p, l, r);
        if (ql <= l && r <= qr) return st[p];
        int m = l + (r - l) / 2;
        T resl = query(left(p), l, m, ql, qr);
        T resr = query(right(p), m + 1, r, ql, qr);
        return F::op(resl, resr);
    }
    void build(int p, int l, int r, const vector<T>& a)
    {
        if (l == r) st[p] = a[l];
        else
        {
            int m = l + (r - l) / 2;
            build(left(p), l, m, a), build(right(p), m + 1, r, a);
            st[p] = F::op(st[left(p)], st[right(p)]);
        }
    }
public:
    LazyST(int n) : n(n) { st.assign(4 * n + 1, F::Tid), lazy.assign(4 * n + 1, F::Fid); }
    LazyST(const vector<T>& a) : LazyST(size(a)) { build(0, 0, n - 1, a); }
    void update(int l, int r, F op) { update(0, 0, n - 1, l, r, op); }
    T query(int l, int r) { return query(0, 0, n - 1, l, r); }
};

int main()
{ _
    exit(0);
}


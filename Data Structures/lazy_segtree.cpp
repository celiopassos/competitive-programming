#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename X, typename T>
struct F1
{
    X add;
    explicit F1(X add) : add(add) {}
    void apply(T& old, int L, int R) const
    {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op, int L, int R)
    {
        add += op.add;
    }
    bool operator==(const F1& op) const { return add == op.add; }
    static T combine(const T& lhs, const T& rhs)
    {
        return lhs + rhs;
    }
};

template<typename T, typename F>
class SegmentTree
{
private:
    const int n; const T Tid; const F Fid;
    vector<T> st; vector<F> lazy;
    int left(int p) const { return 2 * p + 1; }
    int right(int p) const { return 2 * p + 2; }
    void push(int p, int l, int r)
    {
        if (lazy[p] == Fid) return; // may wanna remove this...
        lazy[p].apply(st[p], l, r);
        if (l != r)
        {
            int m = l + (r - l) / 2;
            lazy[left(p)].compose(lazy[p], l, m);
            lazy[right(p)].compose(lazy[p], m + 1, r);
        }
        lazy[p] = Fid;
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
            st[p] = F::combine(st[left(p)], st[right(p)]);
        }
    }
    T query(int p, int l, int r, int ql, int qr)
    {
        if (r < ql || qr < l) return Tid;
        push(p, l, r);
        if (ql <= l && r <= qr) return st[p];
        int m = l + (r - l) / 2;
        T resl = query(left(p), l, m, ql, qr);
        T resr = query(right(p), m + 1, r, ql, qr);
        return F::combine(resl, resr);
    }
public:
    SegmentTree(const vector<T>& a, T Tid, F Fid) : n(sz(a)), Tid(Tid), Fid(Fid)
    {
        st.assign(4 * n + 1, Tid);
        lazy.assign(4 * n + 1, Fid);
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (l == r) st[p] = a[l];
            else
            {
                int m = l + (r - l) / 2;
                build(left(p), l, m), build(right(p), m + 1, r);
                st[p] = F::combine(st[left(p)], st[right(p)]);
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


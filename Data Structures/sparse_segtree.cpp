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

template<typename X, typename T=X>
struct F1
{
    X add;
    explicit F1(X add) : add(add) {}
    void apply_aggregate(T& old, int L, int R) const
    {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op, int L, int R)
    {
        add += op.add;
    }
    bool operator==(const F1& op) const { return add == op.add; }
};

template<typename T, typename F>
class SparseSegmentTree
{
private:
    const int L, R;
    const T Tid; const F Fid;
    vector<T> st; vector<F> lazy;
    T combine(const T& resl, const T& resr)
    {
        return resl + resr;
    }
    vector<int> LEFT, RIGHT;
    int ct = 1;
    int left(int p) { return LEFT[p] == -1 ? (LEFT[p] = ct++) : LEFT[p]; }
    int right(int p) { return RIGHT[p] == -1 ? (RIGHT[p] = ct++) : RIGHT[p]; }
    void push(int p, int l, int r)
    {
        if (lazy[p] == Fid) return; // may wanna remove this...
        lazy[p].apply_aggregate(st[p], l, r);
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
            st[p] = combine(st[left(p)], st[right(p)]);
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
        return combine(resl, resr);
    }
public:
    SparseSegmentTree(int L, int R, int N, T Tid, F Fid) :
        L(L), R(R), Tid(Tid), Fid(Fid)
    {
        st.assign(N, Tid);
        lazy.assign(N, Fid);
        LEFT.assign(N, -1), RIGHT.assign(N, -1);
    }
    void update(int l, int r, F op) { update(0, L, R, l, r, op); }
    T query(int l, int r) { return query(0, L, R, l, r); }
};

int main()
{ _
    exit(0);
}


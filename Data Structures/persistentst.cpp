#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename T>
class PersistentST
{
private:
    const int n;
    const T Tid;
    const function<T(T, T)> op;
    vector<T> st;
    vector<int> left, right, root;
    int ct = 0;
    int create() { return ct++; }
    int copy(int p)
    {
        int q = create();
        st[q] = st[p];
        left[q] = left[p], right[q] = right[p];
        return q;
    }
    void modify(int p, int l, int r, int pos, T value)
    {
        if (l == r) st[p] = value;
        else
        {
            int m = l + (r - l) / 2;
            if (pos <= m) modify(left[p] = copy(left[p]), l, m, pos, value);
            else modify(right[p] = copy(right[p]), m + 1, r, pos, value);
            st[p] = op(st[left[p]], st[right[p]]);
        }
    }
    T query(int p, int l, int r, int ql, int qr)
    {
        if (r < ql || qr < l) return Tid;
        if (ql <= l && r <= qr) return st[p];
        int m = l + (r - l) / 2;
        T resl = query(left[p], l, m, ql, qr);
        T resr = query(right[p], m + 1, r, ql, qr);
        return op(resl, resr);
    }
public:
    PersistentST(const vector<T>& a, T Tid, auto op, int N = 1e7) : n(sz(a)), Tid(Tid), op(op)
    {
        st.assign(N, Tid), left.assign(N, -1), right.assign(N, -1);
        root.push_back(create());
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (l == r) st[p] = a[l];
            else
            {
                int m = l + (r - l) / 2;
                left[p] = create(), right[p] = create();
                build(left[p], l, m), build(right[p], m + 1, r);
                st[p] = op(st[left[p]], st[right[p]]);
            }
        };
        build(0, 0, n - 1);
    }
    void modify(int version, int pos, T value)
    {
        root.push_back(copy(root[version]));
        modify(root.back(), 0, n - 1, pos, value);
    }
    T query(int version, int l, int r)
    {
        return query(root[version], 0, n - 1, l, r);
    }
};

int main()
{ _
    exit(0);
}


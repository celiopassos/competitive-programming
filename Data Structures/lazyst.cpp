template<typename F>
struct LazyST {
    using T = typename F::Type;

    int n;

    vector<typename F::Node> st;
    vector<F> lazy;

    int left(int p) const { return 2 * p + 1; }
    int right(int p) const { return 2 * p + 2; }

    void push(int p) {
        lazy[p].apply(st[p]);
        if (st[p].l != st[p].r) {
            lazy[left(p)].compose(lazy[p]);
            lazy[right(p)].compose(lazy[p]);
        }
        lazy[p] = F();
    }
    void update(int p, int ql, int qr, F op) {
        if (st[p].r < ql || qr < st[p].l) push(p);
        else if (ql <= st[p].l && st[p].r <= qr) {
            lazy[p].compose(op);
            push(p);
        }
        else {
            push(p);
            update(left(p), ql, qr, op);
            update(right(p), ql, qr, op);
            st[p].value = F::op(st[left(p)].value, st[right(p)].value);
        }
    }
    T query(int p, int ql, int qr) {
        if (st[p].r < ql || qr < st[p].l) return F::Id;
        push(p);
        if (ql <= st[p].l && st[p].r <= qr) return st[p].value;
        return F::op(query(left(p), ql, qr), query(right(p), ql, qr));
    }
    void build(int p, int l, int r, const vector<T>& a) {
        st[p].l = l, st[p].r = r;
        if (l == r) st[p].value = a[l];
        else {
            int m = l + (r - l) / 2;
            build(left(p), l, m, a), build(right(p), m + 1, r, a);
            st[p].value = F::op(st[left(p)].value, st[right(p)].value);
        }
    }
    void partition(auto& q, int p, int ql, int qr) {
        if (st[p].r < ql || qr < st[p].l) return;
        push(p);
        if (ql <= st[p].l && st[p].r <= qr) return (void)q.push(p);
        partition(q, left(p), ql, qr);
        partition(q, right(p), ql, qr);
    }
    int binary_search(int p, T prefix, T value) {
        push(p);
        if (st[p].l == st[p].r) return st[p].l + F::cmp(F::op(prefix, st[p].value), value);
        push(left(p));
        if (T x = F::op(prefix, st[left(p)].value); F::cmp(x, value))
            return binary_search(right(p), x, value);
        else
            return binary_search(left(p), prefix, value);
    }

    LazyST(int n) : n(n), st(4 * n + 1), lazy(4 * n + 1, F()) { }
    LazyST(const vector<T>& a) : LazyST((int)size(a)) {
        build(0, 0, n - 1, a);
    }
    void update(int l, int r, F op) {
        update(0, l, r, op);
    }
    T query(int l, int r) {
        return query(0, l, r);
    }
    int lower_bound(T value) {
        return binary_search(0, F::Id, value);
    }
    int lower_bound(int l, int r, T value) {
        static vector<int> q;
        partition(q, 0, l, r);
        int res = r + 1;
        for (auto [idx, prefix] = pair(0, F::Id); idx < (int)size(q); ++idx) {
            auto [p, l, r] = q[idx];
            if (T x = F::op(prefix, st[p]); F::cmp(x, value)) prefix = x;
            else {
                res = binary_search(p, l, r, prefix, value);
                break;
            }
        }
        q.clear();
        return res;
    }
};

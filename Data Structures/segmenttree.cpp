template<typename T>
struct M1 {
    using Type = T;
    inline const static Type Id = Type();
    static Type op(Type x, Type y) { return x + y; }
    static bool cmp(Type x, Type y) { return x < y; }
};

template<typename Monoid>
struct SegmentTree {
    using M = Monoid;
    using T = typename Monoid::Type;
    int n;
    vector<T> st;
    int binary_search(int p, T prefix, T value) {
        while (p < n) if (T x = M::op(prefix, st[p <<= 1]); M::cmp(x, value))
            prefix = x, p |= 1;
        return p - n + M::cmp(M::op(prefix, st[p]), value);
    }
    SegmentTree(int n) : n(n), st(2 * n, M::Id) { }
    SegmentTree(const vector<T>& a) : SegmentTree((int)size(a)) {
        for (int i = 0; i < n; ++i) st[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            st[i] = M::op(st[i << 1], st[i << 1 | 1]);
    }
    void modify(int p, T value) {
        for (st[p += n] = value; p > 1; p >>= 1)
            st[p >> 1] = M::op(st[p & ~1], st[p | 1]);
    }
    T query(int l, int r) {
        T resl = M::Id, resr = M::Id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, st[l++]);
            if (r & 1) resr = M::op(st[--r], resr);
        }
        return M::op(resl, resr);
    }
    int lower_bound(T value) { return lower_bound(0, n - 1, value); }
    // first x in [a, b] with M::cmp(query(a, x), value) == false
    // returns b + 1 if no such x exists
    int lower_bound(int a, int b, T value) {
        static vector<int> left, right;
        for (int l = a + n, r = b + n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left.push_back(l++);
            if (r & 1) right.push_back(--r);
        }
        left.insert(end(left), rbegin(right), rend(left));
        right.clear();
        T prefix M::Id;
        for (size_t i = 0; i < size(left); ++i) {
            int p = st[i];
            if (T x = M::op(prefix, st[p]); M::cmp(x, value)) prefix = x;
            else {
                left.clear();
                return binary_search(p, prefix, value);
            }
        }
        left.clear();
        return b + 1;
    }
};

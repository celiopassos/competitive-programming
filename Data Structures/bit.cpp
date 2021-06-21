template<typename T>
struct G1 {
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static T inv(const T& x) { return -x; }
};
int b(int p) { return p & (-p); }
template<typename Group>
struct BIT {
    using G = Group;
    using T = typename G::Type;
    int n, h;
    vector<T> ft;
    T query(int p) {
        T res = G::Id;
        for (; p; p -= b(p)) res = G::op(ft[p], res);
        return res;
    }
    BIT(int n) : n(n), h(31 - __builtin_clz(n)), ft(n + 1, G::Id) { }
    BIT(const vector<T>& a) : BIT((int)size(a)) {
        for (int i = 1; i <= n; ++i) ft[i] = G::op(ft[i - 1], a[i - 1]);
        for (int i = n; i >= 1; --i) ft[i] = G::op(G::inv(ft[i - b(i)]), ft[i]);
    }
    T query(int l, int r) { return G::op(G::inv(query(l)), query(r + 1)); }
    void update(int p, T value) {
        for (++p; p <= n; p += b(p)) ft[p] = G::op(ft[p], value);
    }
    // first r such that cmp(query(0, r), value) == false
    template<typename S, typename Cmp>
    int lower_bound(S value, Cmp&& cmp) {
        T prefix = G::Id;
        int pos = 0;
        for (int x = h; x >= 0; --x) {
            if (pos + (1 << x) <= n && cmp(G::op(prefix, ft[pos + (1 << x)]), value) == true) {
                pos += 1 << x;
                prefix = G::op(prefix, ft[pos]);
            }
        }
        return pos;
    }
    int lower_bound(T value) {
        return lower_bound(value, less<T>());
    }
};

template<typename T>
struct G1 {
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static T inv(const T& x) { return -x; }
};
int lsb(int b) { return b & -b; }
template<typename Group>
struct BIT {
    using G = Group;
    using T = typename G::Type;
    int n, h;
    vector<T> ft;
    BIT(int n) : n(n), h(__lg(n)), ft(n + 1, G::Id) { }
    BIT(const vector<T>& a) : BIT((int)a.size()) {
        for (int i = 1; i <= n; ++i) ft[i] = G::op(ft[i - 1], a[i - 1]);
        for (int i = n; i >= 1; --i) ft[i] = G::op(G::inv(ft[i - lsb(i)]), ft[i]);
    }
    T query(int p) const {
        T res = G::Id;
        for (++p; p >= 1; p -= lsb(p)) res = G::op(ft[p], res);
        return res;
    }
    T query(int l, int r) const {
        return G::op(G::inv(query(l - 1)), query(r));
    }
    void update(int p, T value) {
        for (++p; p <= n; p += lsb(p)) ft[p] = G::op(ft[p], value);
    }
    // first r such that cmp(query(0, r), value) == false
    template<typename S, typename Cmp>
    int lower_bound(S value, Cmp&& cmp) const {
        T prefix = G::Id;
        int pos = 0;
        for (int x = h; x >= 0; --x) {
            int npos = pos + (1 << x);
            if (npos <= n && cmp(G::op(prefix, ft[npos]), value) == true) {
                pos = npos;
                prefix = G::op(prefix, ft[pos]);
            }
        }
        return pos;
    }
    int lower_bound(T value) const {
        return lower_bound(value, less<T>());
    }
};

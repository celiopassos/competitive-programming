template<typename T>
struct BIT {
    static int lsb(int b) { return b & -b; }
    int N, h;
    vector<T> ft;
    BIT(int N) : N(N), h(__lg(N)), ft(N + 1, T()) { }
    template<typename Iterator>
    BIT(Iterator first, Iterator last) : BIT(int(last - first)) {
        partial_sum(first, last, ft.begin() + 1, plus<T>());
        for (int i = N; i >= 1; --i) {
            ft[i] = ft[i] - ft[i - lsb(i)];
        }
    }
    T query(int p) const {
        T res = T();
        for (; p >= 1; p -= lsb(p)) {
            res = res + ft[p];
        }
        return res;
    }
    T query(int l, int r) const {
        return query(r) - query(l);
    }
    void update(int p, T value) {
        for (++p; p <= N; p += lsb(p)) {
            ft[p] = ft[p] + value;
        }
    }
    // returns first r such that pred(query(0, r + 1)) == false (N if no such r exists)
    template<typename Pred>
    int find_right(Pred&& pred) const {
        T prefix = T();
        int pos = 0;
        for (int x = h; x >= 0; --x) {
            int npos = pos + (1 << x);
            if (npos > N) continue;
            T nprefix = prefix + ft[npos];
            if (pred(nprefix)) {
                pos = npos;
                prefix = nprefix;
            }
        }
        return pos;
    }
    int lower_bound(T value) const {
        return find_right([value](T x) { return x < value; });
    }
};

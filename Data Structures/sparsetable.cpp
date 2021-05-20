// K > floor(log(n))

template<typename T, int K>
struct SparseTable {
    int n;
    function<T(T, T)> op;
    vector<array<T, K>> st;
    vector<int> log;
    SparseTable(const vector<T>& a, auto op) : n((int)size(a)), op(op), st(n), log(n + 1) {
        for (int x = 1; x <= n; ++x) log[x] = __builtin_clz(1) - __builtin_clz(x);
        assert(log[n] < K);
        for (int i = 0; i < n; ++i) st[i][0] = a[i];
        for (int x = 1; x <= log[n]; ++x)
            for (int i = 0; i + (1 << x) <= n; ++i)
                st[i][x] = op(st[i][x - 1], st[i + (1 << (x - 1))][x - 1]);
    }
    T query(int l, int r) const {
        assert(l <= r);
        int x = log[r - l + 1];
        return op(st[l][x], st[r - (1 << x) + 1][x]);
    }
};

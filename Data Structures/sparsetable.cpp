// K > floor(log(n))
template<int K, typename T, typename Op>
struct SparseTable {
    int n;
    Op op;
    vector<array<T, K>> st;
    vector<int> log;
    SparseTable(const vector<T>& a, Op op = Op()) : n((int)size(a)), op(op), st(n), log(n + 1) {
        for (int x = 2; x <= n; ++x) log[x] = 1 + log[x >> 1];
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
template<typename T>
struct MinFunctor {
    T operator()(T x, T y) const { return min(x, y); }
};
template<int K, typename T>
using RMQ = SparseTable<K, T, MinFunctor<T>>;

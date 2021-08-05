// K > floor(log(N))
template<int K, typename T, typename Op>
struct SparseTable {
    int N;
    Op op;
    vector<array<T, K>> st;
    vector<int> log;
    template<typename Iterator>
    SparseTable(Iterator first, Iterator last, Op op = Op()) :  op(op), N(int(last - first)), st(N), log(N) {
        for (int x = 2; x <= N; ++x) {
            log[x] = 1 + log[x >> 1];
        }
        assert(log[N] < K);
        for (int i = 0; i < N; ++i) {
            st[i][0] = a[i];
        }
        for (int x = 1; x <= log[N]; ++x) {
            for (int i = 0; i + (1 << x) <= N; ++i) {
                st[i][x] = op(st[i][x - 1], st[i + (1 << (x - 1))][x - 1]);
            }
        }
    }
    T query(int l, int r) const {
        assert(l < r);
        int x = log[r - l];
        return op(st[l][x], st[r - (1 << x)][x]);
    }
};
template<typename T>
struct MinFunctor {
    T operator()(T x, T y) const { return min(x, y); }
};
template<int K, typename T>
using RMQ = SparseTable<K, T, MinFunctor<T>>;

template <typename T, typename Op>
struct SparseTable {
  int N;
  Op op;
  std::vector<int> log;
  std::vector<std::vector<T>> st;
  template <typename Iterator>
  SparseTable(Iterator first, Iterator last, Op op = Op()) : N(last - first), op(op), log(N + 1) {
    for (int x = 2; x <= N; ++x) {
      log[x] = 1 + log[x >> 1];
    }
    st.resize(log[N] + 1);
    st[0] = std::vector<T>(first, last);
    for (int x = 0; x < log[N]; ++x) {
      st[x + 1].resize(N);
      for (int i = 0; i + (1 << (x + 1)) <= N; ++i) {
        st[x + 1][i] = op(st[x][i], st[x][i + (1 << x)]);
      }
    }
  }
  T query(int l, int r) const {
    assert(l < r);
    int x = log[r - l];
    return op(st[x][l], st[x][r - (1 << x)]);
  }
};
template <typename T>
struct MinFunctor {
  T operator()(T x, T y) const {
    return std::min(x, y);
  }
};
template <typename T>
using RMQ = SparseTable<T, MinFunctor<T>>;

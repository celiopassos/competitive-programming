template <typename T>
struct SegmentTree {
  int N;
  std::vector<T> st;

  SegmentTree(int N) : N(N), st(2 * N) {}
  template <typename Iterator>
  SegmentTree(Iterator first, Iterator last) : SegmentTree(last - first) {
    std::copy(first, last, st.begin() + N);
    for (int p = N - 1; p > 0; --p) {
      st[p] = st[p << 1] + st[p << 1 | 1];
    }
  }

  void modify(int p, T value) {
    p += N;
    st[p] = value;
    while (p > 1) {
      p >>= 1;
      st[p] = st[p << 1] + st[p << 1 | 1];
    }
  }

  T query(int l, int r) const {
    T resl = T(), resr = T();
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        resl = resl + st[l];
        ++l;
      }
      if (r & 1) {
        --r;
        resr = st[r] + resr;
      }
    }
    return resl + resr;
  }
};

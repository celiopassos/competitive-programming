template <typename T>
struct BIT {
  static int lsb(int b) {
    return b & -b;
  }
  int N, h;
  std::vector<T> ft;
  BIT(int N) : N(N), h(std::__lg(N)), ft(N + 1, T()) {}
  template <typename Iterator>
  BIT(Iterator first, Iterator last) : BIT(last - first) {
    for (int i = 1; i <= N; ++i) {
      ft[i] = first[i - 1] + ft[i - 1];
    }
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
  // returns largest r such that pred(query(0, r)) == true
  template <typename Pred>
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

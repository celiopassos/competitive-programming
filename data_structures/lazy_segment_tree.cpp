template <typename T, typename F>
struct LazySegmentTree {
  struct Node {
    T value = T();
    F lazy = F();
    int l, r;
  };

  int N;
  std::vector<Node> st;

  int left(int p) const {
    return 2 * p + 1;
  }
  int right(int p) const {
    return 2 * p + 2;
  }

  void push(int p) {
    if (st[p].l + 1 == st[p].r) return;
    for (int q : {left(p), right(p)}) {
      st[p].lazy.apply(st[q]);
      st[q].lazy.compose(st[p].lazy);
    }
    st[p].lazy = F();
  }

  void update(int p, int ql, int qr, F f) {
    if (st[p].r <= ql || qr <= st[p].l || f.can_break(st[p])) {
      return;
    } else if (ql <= st[p].l && st[p].r <= qr && f.can_apply(st[p])) {
      f.apply(st[p]);
      st[p].lazy.compose(f);
    } else {
      push(p);
      update(left(p), ql, qr, f);
      update(right(p), ql, qr, f);
      st[p].value = st[left(p)].value + st[right(p)].value;
    }
  }

  T query(int p, int ql, int qr) {
    if (st[p].r <= ql || qr <= st[p].l) {
      return T();
    } else if (ql <= st[p].l && st[p].r <= qr) {
      return st[p].value;
    } else {
      push(p);
      return query(left(p), ql, qr) + query(right(p), ql, qr);
    }
  }

  template <typename Iterator>
  void build(int p, int l, int r, Iterator first) {
    st[p].l = l, st[p].r = r;
    if (l + 1 == r) {
      st[p].value = first[l];
    } else {
      int m = l + (r - l) / 2;
      build(left(p), l, m, first), build(right(p), m, r, first);
      st[p].value = st[left(p)].value + st[right(p)].value;
    }
  }

  template <typename Iterator>
  LazySegmentTree(Iterator first, Iterator last) : N(last - first), st(4 * N) {
    build(0, 0, N, first);
  }

  T query(int l, int r) {
    return query(0, l, r);
  }

  void update(int l, int r, F f) {
    update(0, l, r, f);
  }
};

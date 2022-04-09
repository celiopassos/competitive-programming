long long sum_idx(long long n) {
  return n * (n + 1) / 2;
}

template <typename T>
struct RangeAddLinear {
  // adds a * (i - s) + b to the element in position i
  T a, b;
  RangeAddLinear(T a = 0, T b = 0, int s = 0) : a(a), b(b - s * a) {}
  template <typename Node>
  bool can_break(const Node& p) const {
    return false;
  }
  template <typename Node>
  bool can_apply(const Node& p) const {
    return true;
  }
  template <typename Node>
  void apply(Node& p) const {
    auto& v = p.value;
    v += a * (sum_idx(p.r - 1) - sum_idx(p.l - 1)) + (p.r - p.l) * b;
  }
  void compose(RangeAddLinear op) {
    a += op.a, b += op.b;
  }
};

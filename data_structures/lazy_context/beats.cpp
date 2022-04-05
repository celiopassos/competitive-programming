template <typename T>
struct BeatsMonoid {
  static const T inf = Clamp<T>::inf;
  T sum, low[2], high[2];
  int cntlow, cnthigh;
  BeatsMonoid() : sum(0), low{+inf, +inf}, high{-inf, -inf}, cntlow(0), cnthigh(0) {}
  BeatsMonoid(T x) : sum(x), low{x, +inf}, high{x, -inf}, cntlow(1), cnthigh(1) {}
  BeatsMonoid operator+(const BeatsMonoid& rhs) const {
    const auto& lhs = *this;
    BeatsMonoid res;
    res.sum = lhs.sum + rhs.sum;
    res.low[0] = std::min(lhs.low[0], rhs.low[0]);
    res.high[0] = std::max(lhs.high[0], rhs.high[0]);
    int lowl = lhs.low[0] == res.low[0] ? (res.cntlow += lhs.cntlow, 1) : 0;
    int lowr = rhs.low[0] == res.low[0] ? (res.cntlow += rhs.cntlow, 1) : 0;
    int highl = lhs.high[0] == res.high[0] ? (res.cnthigh += lhs.cnthigh, 1) : 0;
    int highr = rhs.high[0] == res.high[0] ? (res.cnthigh += rhs.cnthigh, 1) : 0;
    res.low[1] = std::min(lhs.low[lowl], rhs.low[lowr]);
    res.high[1] = std::max(lhs.high[highl], rhs.high[highr]);
    return res;
  }
};
template <typename T>
struct BeatsUpdate {
  Clamp<T> cl;
  BeatsUpdate() {}
  template <typename... Args>
  BeatsUpdate(Args... args) : cl(args...) {}
  template <typename Node>
  bool can_break(const Node& p) const {
    for (auto x : {p.value.low[0], p.value.high[0]}) {
      if (cl(x) != x) return false;
    }
    return true;
  }
  template <typename Node>
  bool can_apply(const Node& p) const {
    const auto &low = p.value.low, high = p.value.high;
    return cl(low[0]) == cl(high[0]) || (cl(low[0]) != cl(low[1]) && cl(high[0]) != cl(high[1]));
  }
  template <typename Node>
  void apply(Node& p) const {
    int len = p.r - p.l;
    auto& [sum, low, high, cntlow, cnthigh] = p.value;
    if (T x = cl(high[0]); cl(low[0]) == x) {
      p.value = BeatsMonoid<T>(x);
      sum = x * len;
      cntlow = cnthigh = len;
    } else {
      sum -= cntlow * low[0] + cnthigh * high[0];
      sum += cl.add * (len - cntlow - cnthigh);
      for (int t : {0, 1}) {
        low[t] = cl(low[t]);
        high[t] = cl(high[t]);
      }
      sum += cntlow * low[0] + cnthigh * high[0];
    }
  }
  void compose(BeatsUpdate op) {
    cl = op.cl * cl;
  }
};

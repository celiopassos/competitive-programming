#ifndef ALGORITHMS_OTHER_EXCLUSIVE_HPP
#define ALGORITHMS_OTHER_EXCLUSIVE_HPP

// op should map (X, Y) -> Y
template <typename X, typename Y, typename Op>
std::vector<Y> exclusive(const std::vector<X>& a, Y Id, Op&& op) {
  int N = a.size();
  std::vector<Y> res(N, Id);
  for (int b = std::__lg(N - 1); b >= 0; --b) {
    for (int i = N - 1; i >= 0; --i) {
      res[i] = res[i >> 1];
    }
    for (int i = 0; i < N; ++i) {
      int idx = (i >> b) ^ 1;
      if (idx >= N) continue;
      res[idx] = op(a[i], res[idx]);
    }
  }
  return res;
}

#endif  // ALGORITHMS_OTHER_EXCLUSIVE_HPP

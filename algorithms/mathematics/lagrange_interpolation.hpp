#ifndef ALGORITHMS_MATHEMATICS_LAGRANGE_INTERPOLATION_HPP
#define ALGORITHMS_MATHEMATICS_LAGRANGE_INTERPOLATION_HPP

#include "algorithms/common"
#include "algorithms/mathematics/combinatorics"

template <typename T>
T interpolate(const std::vector<T>& y, T x) {
  int N = y.size();
  std::vector<T> pref(N), suff(N);
  pref[0] = suff[N - 1] = 1;
  for (int i = 0; i + 1 < N; ++i) {
    pref[i + 1] = pref[i] * (x - i);
  }
  for (int i = N - 1; i > 0; --i) {
    suff[i - 1] = suff[i] * (x - i);
  }
  const auto& C = combinatorics<T>;
  T res = 0;
  for (int i = 0, sgn = (N % 2 ? +1 : -1); i < N; ++i, sgn *= -1) {
    res += y[i] * sgn * pref[i] * suff[i] * C.rfact[i] * C.rfact[N - 1 - i];
  }
  return res;
}

#endif  // ALGORITHMS_MATHEMATICS_LAGRANGE_INTERPOLATION_HPP

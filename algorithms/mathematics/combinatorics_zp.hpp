#ifndef ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP
#define ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP

#include "algorithms/mathematics/combinatorics"
#include "algorithms/mathematics/modular_arithmetic"

template <unsigned P>
struct Combinatorics<Z<P>> {
  std::vector<Z<P>> fact, rfact, r;
  Combinatorics(int N) : fact(N), rfact(N), r(N) {
    fact[0] = fact[1] = rfact[0] = rfact[1] = r[1] = 1;
    for (int i = 2; i < N; ++i) {
      r[i] = -(P / i * r[P % i]);
      rfact[i] = r[i] * rfact[i - 1];
      fact[i] = i * fact[i - 1];
    }
  }
  Z<P> C(int n, int k) const {
    return k < 0 || n < k ? 0 : fact[n] * rfact[k] * rfact[n - k];
  }
  Z<P> S(int n, int k) const {
    return k == 0 ? n == 0 : C(n + k - 1, k - 1);
  }
};

#endif  // ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP

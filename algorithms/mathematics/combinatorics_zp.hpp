#ifndef ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP
#define ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP

#include "algorithms/mathematics/combinatorics"
#include "algorithms/mathematics/modular_arithmetic"

#include <vector>

template <unsigned P>
struct Combinatorics<Z<P>> {
  static const Combinatorics<Z<P>>& get_instance() {
    static Combinatorics<Z<P>> C(1 << 20);
    return C;
  }

  std::vector<Z<P>> fact, rfact, r;

  Combinatorics(int N) : fact(N), rfact(N), r(N) {
    fact[0] = fact[1] = rfact[0] = rfact[1] = r[1] = 1;
    for (int i = 2; i < N; ++i) {
      r[i] = -(P / i * r[P % i]);
      rfact[i] = r[i] * rfact[i - 1];
      fact[i] = i * fact[i - 1];
    }
  }

  static Z<P> C(int n, int k) {
    const auto& comb = get_instance();
    return k < 0 || n < k ? 0 : k == 0 || k == n ? 1 : comb.fact[n] * comb.rfact[k] * comb.rfact[n - k];
  }

  static Z<P> S(int n, int k) {
    return k == 0 ? n == 0 : C(n + k - 1, k - 1);
  }
};

#endif  // ALGORITHMS_MATHEMATICS_COMBINATORICS_ZP_HPP

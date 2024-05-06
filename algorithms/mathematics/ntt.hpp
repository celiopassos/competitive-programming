#ifndef ALGORITHMS_MATHEMATICS_NTT_HPP
#define ALGORITHMS_MATHEMATICS_NTT_HPP

#include "algorithms/mathematics/fft"
#include "algorithms/mathematics/modular_arithmetic"

constexpr int ntt_mod = 998244353;
template <>
struct RootOfUnity<Z<ntt_mod>> {
  static constexpr Z<ntt_mod> g = Z<ntt_mod>(3);
  static Z<ntt_mod> root_of_unity(int N) {
    return pow(g, int(ntt_mod - 1) / N);
  }
};

#endif  // ALGORITHMS_MATHEMATICS_NTT_HPP

#ifndef ALGORITHMS_MATHEMATICS_CONVOLUTION_ZP_HPP
#define ALGORITHMS_MATHEMATICS_CONVOLUTION_ZP_HPP

#include "algorithms/mathematics/convolution_base"
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

template <>
struct Convolution<Z<ntt_mod>> {
  static constexpr int naive_threshold = 64;

  static std::vector<Z<ntt_mod>> convolution(std::vector<Z<ntt_mod>> p, std::vector<Z<ntt_mod>> q) {
    int N = p.size(), M = q.size();
    if (N == 0 || M == 0) {
      return {};
    } else if (std::min(N, M) <= naive_threshold) {
      std::vector<Z<ntt_mod>> res(N + M - 1);
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
          res[i + j] += p[i] * q[j];
        }
      }
      return res;
    } else {
      int R = N + M - 1, K = 1;
      while (K < R) K <<= 1;
      p.resize(K);
      q.resize(K);
      auto phat = FFT<Z<ntt_mod>>::dft(std::move(p));
      auto qhat = FFT<Z<ntt_mod>>::dft(std::move(q));
      for (int i = 0; i < K; ++i) {
        phat[i] *= qhat[i];
      }
      auto res = FFT<Z<ntt_mod>>::idft(std::move(phat));
      res.resize(R);
      return res;
    }
  }
};

#endif // ALGORITHMS_MATHEMATICS_CONVOLUTION_ZP_HPP

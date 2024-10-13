#ifndef ALGORITHMS_MATHEMATICS_CONVOLUTION_MOD_HPP
#define ALGORITHMS_MATHEMATICS_CONVOLUTION_MOD_HPP

#include "algorithms/mathematics/modular_arithmetic"
#include "algorithms/mathematics/convolution_base"
#include "algorithms/mathematics/convolution_complex"

#include <complex>

template <unsigned P>
struct Convolution<Z<P>> {
  static constexpr int naive_threshold = 64;
  static constexpr int magic = 1 << 15;

  static std::vector<Z<P>> convolution(std::vector<Z<P>> p, std::vector<Z<P>> q) {
    int N = p.size(), M = q.size();
    if (N == 0 || M == 0) {
      return {};
    } else if (std::min(N, M) <= naive_threshold) {
      std::vector<Z<P>> res(N + M - 1);
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
          res[i + j] += p[i] * q[j];
        }
      }
      return res;
    } else {
      std::vector<std::complex<double>> A(N), B0(M), B1(M);
      for (int i = 0; i < N; ++i) {
        A[i].real(p[i].value % magic);
        A[i].imag(p[i].value / magic);
      }
      for (int j = 0; j < M; ++j) {
        B0[j] = q[j].value % magic;
        B1[j] = q[j].value / magic;
      }
      int K = N + M - 1;
      std::vector<Z<P>> res(K);
      auto x = A * B0;
      for (int i = 0; i < K; ++i) {
        res[i] = llround(x[i].real());
        res[i] += magic * (llround(x[i].imag()) % P);
      }
      if constexpr (magic <= P) {
        auto y = A * B1;
        for (int i = 0; i < K; ++i) {
          res[i] += magic * (llround(y[i].real()) % P);
          res[i] += (1LL * magic * magic % P) * (llround(y[i].imag()) % P);
        }
      }
      return res;
    }
  }
};


#endif  // ALGORITHMS_MATHEMATICS_CONVOLUTION_MOD_HPP

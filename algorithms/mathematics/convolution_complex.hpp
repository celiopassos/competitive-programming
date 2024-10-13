#ifndef ALGORITHMS_MATHEMATICS_CONVOLUTION_COMPLEX_HPP
#define ALGORITHMS_MATHEMATICS_CONVOLUTION_COMPLEX_HPP

#include "algorithms/mathematics/convolution_base"
#include "algorithms/mathematics/fft"

#include <complex>

template <typename T>
struct RootOfUnity<std::complex<T>> {
  inline static const T PI = std::acos(T(-1));
  static std::complex<T> root_of_unity(int N) {
    return std::polar<T>(1, 2 * PI / N);
  }
};

template <typename T>
struct Convolution<std::complex<T>> {
  static constexpr int naive_threshold = 64;

  static std::vector<std::complex<T>> convolution(std::vector<std::complex<T>> p, std::vector<std::complex<T>> q) {
    int N = p.size(), M = q.size();
    if (N == 0 || M == 0) {
      return {};
    } else if (std::min(N, M) <= naive_threshold) {
      std::vector<std::complex<T>> res(N + M - 1);
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
      auto phat = FFT<std::complex<T>>::dft(std::move(p));
      auto qhat = FFT<std::complex<T>>::dft(std::move(q));
      for (int i = 0; i < K; ++i) {
        phat[i] *= qhat[i];
      }
      auto res = FFT<std::complex<T>>::idft(std::move(phat));
      res.resize(R);
      return res;
    }
  }
};

#endif // ALGORITHMS_MATHEMATICS_CONVOLUTION_COMPLEX_HPP

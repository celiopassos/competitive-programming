#ifndef ALGORITHMS_MATHEMATICS_FFT_COMPLEX_HPP
#define ALGORITHMS_MATHEMATICS_FFT_COMPLEX_HPP

#include "algorithms/mathematics/fft"

#include <complex>

template <typename T>
struct RootOfUnity<std::complex<T>> {
  inline static const T PI = std::acos(T(-1));
  static std::complex<T> root_of_unity(int N) {
    return std::polar<T>(1, 2 * PI / N);
  }
};

#endif  // ALGORITHMS_MATHEMATICS_FFT_COMPLEX_HPP

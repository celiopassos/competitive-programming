#ifndef ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_ZP_HPP
#define ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_ZP_HPP

#include "algorithms/mathematics/combinatorics_zp"
#include "algorithms/mathematics/convolution_zp"
#include "algorithms/mathematics/fft"
#include "algorithms/mathematics/formal_power_series"

template <>
FormalPowerSeries<Z<ntt_mod>> inv(const FormalPowerSeries<Z<ntt_mod>>& P) {
  using F = FormalPowerSeries<Z<ntt_mod>>;
  using T = Z<ntt_mod>;
  assert(!P.empty() && P[0] != 0);
  std::vector<T> Q = {1 / P[0]};
  int N = P.size(), K = 1;
  while (K < N) {
    K *= 2;
    Q.resize(2 * K);
    auto Qhat = FFT<T>::dft(std::move(Q));
    F P0(2 * K);
    std::copy_n(P.begin(), std::min(K, N), P0.begin());
    auto Phat = FFT<T>::dft(std::move(P0));
    for (int i = 0; i < 2 * K; ++i) {
      Qhat[i] *= 2 - Phat[i] * Qhat[i];
    }
    Q = FFT<T>::idft(std::move(Qhat));
    Q.resize(K);
  }
  Q.resize(N);
  return F(Q);
}


#endif  // ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_ZP_HPP

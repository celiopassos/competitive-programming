#include "algorithms/mathematics/formal_power_series"
#include "algorithms/mathematics/convolution_zp"

// Returns the coefficients of (x)_N in the monomial basis.
template <typename T>
FormalPowerSeries<T> stirling_numbers_of_the_first_kind(int N) {
  if (N == 0) {
    return {1};
  }
  auto f = stirling_numbers_of_first_kind<T>(N / 2);
  auto g = f * taylor_shift<T>(f, -N / 2);
  if (N % 2) {
    FormalPowerSeries<T> h = {-(N - 1), 1};
    g *= h;
  }
  return g;
}

// Returns the coefficients of x^N  in the basis of falling factorials.
template <typename T>
FormalPowerSeries<T> stirling_numbers_of_the_second_kind(int N) {
  FormalPowerSeries<T> y(N + 1, 1);
  for (int i = 0; i <= N; ++i) {
    T x = i;
    for (int n = N; n; n >>= 1) {
      if (n & 1) {
        y[i] *= x;
      }
      x *= x;
    }
  }
  return falling_factorials::interpolate(y);
}


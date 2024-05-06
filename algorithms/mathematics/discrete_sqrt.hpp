#ifndef ALGORITHMS_MATHEMATICS_DISCRETE_SQRT_HPP
#define ALGORITHMS_MATHEMATICS_DISCRETE_SQRT_HPP

#include <chrono>
#include <random>

#include "algorithms/mathematics/modular_arithmetic"

template <unsigned P>
std::pair<bool, Z<P>> sqrt(Z<P> alpha) {
  if (pow(alpha, (P - 1) / 2) != 1) {
    return {false, 0};  // failed
  }
  static Z<P> alpha_;
  alpha_ = alpha;
  struct R {
    Z<P> a, b;
    R operator*(const R& rhs) const {
      return R{a * rhs.a + alpha_ * b * rhs.b, a * rhs.b + b * rhs.a};
    }
  };
  std::uniform_int_distribution<unsigned> unif(0, P - 1);
  while (true) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    Z<P> y = unif(rng);
    if (y * y == alpha) {
      return {true, y};
    }
    auto x = R{y, 1};
    R pow{1, 0};
    for (int p = (P - 1) / 2; p; p >>= 1) {
      if (p & 1) {
        pow = pow * x;
      }
      x = x * x;
    }
    if (pow.b != 0) {
      return {true, 1 / pow.b};
    }
  }
}

#endif  // ALGORITHMS_MATHEMATICS_DISCRETE_SQRT_HPP

#ifndef ALGORITHMS_MATHEMATICS_CRT_HPP
#define ALGORITHMS_MATHEMATICS_CRT_HPP

#include "algorithms/common"

template <typename T>
struct CRT {
  T a, mod;

  CRT() : a(0), mod(1) {}

  CRT(T a_, T mod_) : a(a_), mod(mod_) {
    a %= mod;
    if (a < 0) a += mod;
  }

  CRT operator+(CRT rhs) const {
    T x, y;
    T g = extended_gcd(mod, rhs.mod, x, y);
    if (a == -1 || rhs.a == -1 || (a - rhs.a) % g) {
      CRT res;
      res.a = -1;
      return res;
    }
    T lcm = mod / g * rhs.mod;
    return CRT(a + (rhs.a - a) / g * mod * x, lcm);
  }
};

#endif  // ALGORITHMS_MATHEMATICS_CRT_HPP

#ifndef ALGORITHMS_MATHEMATICS_DIOPHANTINE_HPP
#define ALGORITHMS_MATHEMATICS_DIOPHANTINE_HPP

#include "algorithms/mathematics/extended_gcd"

template <typename T>
bool diophantine(T a, T b, T c, T& x, T& y) {
  T g = extended_gcd<T>(a, b, x, y);
  if (c % g != 0) return false;
  x *= c / g;
  y *= c / g;
  return true;
}

#endif  // ALGORITHMS_MATHEMATICS_DIOPHANTINE_HPP

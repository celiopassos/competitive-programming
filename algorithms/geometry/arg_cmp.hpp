#ifndef ALGORITHMS_GEOMETRY_ARG_CMP_HPP
#define ALGORITHMS_GEOMETRY_ARG_CMP_HPP

#include <complex>

template <typename T>
int up(std::complex<T> a) {
  if (a.x() == 0 && a.y() == 0) return 0;
  return a.y() > 0 || (a.y() == 0 && a.x() < 0) ? +1 : -1;
}

// Sorts by atan2.
template <typename T>
bool arg_cmp(std::complex<T> a, std::complex<T> b) {
  return up(a) == up(b) ? cross(a, b) > 0 : up(a) < up(b);
}

#endif  // ALGORITHMS_GEOMETRY_ARG_CMP_HPP

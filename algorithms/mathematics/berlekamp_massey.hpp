#ifndef ALGORITHMS_MATHEMATICS_BERLEKAMP_MASSEY_HPP
#define ALGORITHMS_MATHEMATICS_BERLEKAMP_MASSEY_HPP

#include <algorithm>
#include <vector>

template <typename T>
std::vector<T> berlekamp_massey(const std::vector<T>& s) {
  std::vector<T> c, b = {0};
  for (int i = 0; i < s.size(); ++i) {
    T d = s[i];
    for (int j = 0; j < c.size(); ++j) {
      d -= c[j] * s[i - 1 - j];
    }
    bool length_change = false;
    std::vector<T> nb;
    if (d != 0) {
      if (c.size() < b.size()) {
        length_change = true;
        nb = c;
        c.insert(c.end(), b.size() - c.size(), 0);
      }
      for (int j = 0; j < b.size(); ++j) {
        c[j] += d * b[j];
      }
    }
    if (length_change) {
      T inv = 1 / d;
      for (int j = 0; j < nb.size(); ++j) {
        nb[j] *= -inv;
      }
      nb.insert(nb.begin(), inv);
      std::swap(b, nb);
    } else {
      b.insert(b.begin(), 0);
    }
  }
  return c;
}

#endif  // ALGORITHMS_MATHEMATICS_BERLEKAMP_MASSEY_HPP

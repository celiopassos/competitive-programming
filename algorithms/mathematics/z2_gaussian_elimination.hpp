#ifndef ALGORITHMS_MATHEMATICS_Z2_GAUSSIAN_ELIMINATION_HPP
#define ALGORITHMS_MATHEMATICS_Z2_GAUSSIAN_ELIMINATION_HPP

#include <bitset>

#include "algorithms/common"

template <int N>
struct Z2GaussianElimination {
  using V = std::bitset<N>;
  V basis[N], alpha[N];
  int dim = 0, first[N];

  std::pair<int, V> reduce(V& x) const {
    V coef;
    for (int i = 0; i < N; ++i) {
      if (x[i] == 0) continue;
      if (basis[i] == 0) return std::pair(i, coef);
      x ^= basis[i], coef ^= alpha[i];
    }
    return std::pair(-1, coef);
  }

  bool insert(V x) {
    auto [i, coef] = reduce(x);
    if (i == -1) return false;
    basis[i] = x;
    alpha[i] = coef;
    alpha[i][dim] = 1;
    first[dim] = i;
    ++dim;
    return true;
  }

  std::pair<bool, V> solve(V x) const {
    auto [i, coef] = reduce(x);
    return std::pair(i == -1, coef);
  }

  void exchange(int r, V x) {
    auto [k, coef] = reduce(x);
    assert(k == -1);
    assert(coef[r] == 1);
    for (int i = 0; i < N; ++i) {
      if (alpha[i][r]) {
        alpha[i] ^= coef;
        alpha[i][r] = 1;
      }
    }
  }
};

#endif  // ALGORITHMS_MATHEMATICS_Z2_GAUSSIAN_ELIMINATION_HPP

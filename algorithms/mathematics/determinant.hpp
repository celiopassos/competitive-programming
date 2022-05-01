#ifndef ALGORITHMS_MATHEMATICS_DETERMINANT_HPP
#define ALGORITHMS_MATHEMATICS_DETERMINANT_HPP

#include "algorithms/mathematics/matrix"

#include <algorithm>
#include <cassert>

template <typename T>
T determinant(Matrix<T> A) {
  int N = A.size();
  assert(N == A[0].size());
  T det = 1;
  for (int x = 0; x < N; ++x) {
    int sel = -1;
    for (int i = x; i < N; ++i) {
      if (A[i][x] != 0) {
        sel = i;
        break;
      }
    }
    if (sel == -1) return 0;
    if (sel != x) {
      std::swap(A[sel], A[x]);
      det *= -1;
    }
    det *= A[x][x];
    for (int i = 0; i < N; ++i) {
      if (i == x) continue;
      T c = A[i][x] / A[x][x];
      for (int j = x; j < N; ++j) {
        A[i][j] -= c * A[x][j];
      }
    }
  }
  return det;
}

#endif  // ALGORITHMS_MATHEMATICS_DETERMINANT_HPP

#ifndef ALGORITHMS_MATHEMATICS_GAUSSIAN_ELIMINATION_HPP
#define ALGORITHMS_MATHEMATICS_GAUSSIAN_ELIMINATION_HPP

#include "algorithms/mathematics/matrix"

#include <algorithm>
#include <utility>
#include <vector>

template <typename T>
struct GaussianElimination {
  int N, M;
  Matrix<T> A, E;
  std::vector<int> pivot;
  int rank, nullity;

  // Time complexity: O(std::min(N, M)NM).
  GaussianElimination(const Matrix<T>& A_) : A(A_) {
    N = A.size(), M = A[0].size();
    E = Matrix<T>(N, std::vector<T>(N));
    for (int i = 0; i < N; ++i) {
      E[i][i] = 1;
    }
    rank = 0, nullity = M;
    pivot.assign(M, -1);
    for (int col = 0, row = 0; col < M && row < N; ++col) {
      int sel = -1;
      for (int i = row; i < N; ++i) {
        if (A[i][col] != 0) {
          sel = i;
          break;
        }
      }
      if (sel == -1) continue;
      if (sel != row) {
        std::swap(A[sel], A[row]);
        std::swap(E[sel], E[row]);
      }
      for (int i = 0; i < N; ++i) {
        if (i == row) continue;
        T c = A[i][col] / A[row][col];
        for (int j = col; j < M; ++j) {
          A[i][j] -= c * A[row][j];
        }
        for (int j = 0; j < N; ++j) {
          E[i][j] -= c * E[row][j];
        }
      }
      pivot[col] = row++;
      ++rank, --nullity;
    }
  }

  // Time complexity: O(N^2 + M).
  std::pair<bool, std::vector<T>> solve(std::vector<T> b, bool reduced = false) const {
    assert(N == b.size());
    if (!reduced) {
      b = E * b;
    }
    std::vector<T> x(M);
    for (int j = 0; j < M; ++j) {
      if (pivot[j] == -1) continue;
      x[j] = b[pivot[j]] / A[pivot[j]][j];
      b[pivot[j]] = 0;
    }
    for (int i = 0; i < N; ++i) {
      if (b[i] != 0) return std::pair(false, x);
    }
    return std::pair(true, x);
  }

  // Time complexity: O(nullity * NM).
  std::vector<std::vector<T>> kernel_basis() const {
    std::vector<std::vector<T>> basis;
    std::vector<T> e(M);
    for (int j = 0; j < M; ++j) {
      if (pivot[j] != -1) continue;
      e[j] = 1;
      auto y = solve(A * e, true).second;
      e[j] = 0, y[j] = -1;
      basis.push_back(y);
    }
    return basis;
  }

  // Time complexity: O(N^3).
  Matrix<T> inverse() const {
    assert(N == M);
    assert(rank == N);
    Matrix<T> res;
    std::vector<T> e(N);
    for (int i = 0; i < N; ++i) {
      e[i] = 1;
      auto x = solve(e).second;
      for (int j = 0; j < N; ++j) {
        res[j][i] = x[j];
      }
      e[i] = 0;
    }
    return res;
  }
};

#endif  // ALGORITHMS_MATHEMATICS_GAUSSIAN_ELIMINATION_HPP

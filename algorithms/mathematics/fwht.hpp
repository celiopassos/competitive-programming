#ifndef ALGORITHMS_MATHEMATICS_FWHT_HPP
#define ALGORITHMS_MATHEMATICS_FWHT_HPP

#include "algorithms/common"

#include <array>

namespace fwht {

template <typename T>
using Matrix = std::array<std::array<T, 2>, 2>;

template <typename T>
Matrix<T> adjugate(Matrix<T> M) {
  std::swap(M[0][0], M[1][1]);
  M[0][1] *= -1;
  M[1][0] *= -1;
  return M;
}

template <typename T>
T determinant(Matrix<T> M) {
  return M[0][0] * M[1][1] - M[0][1] * M[1][0];
}

template <typename T>
Matrix<T> inverse(Matrix<T> M) {
  T det = determinant(M);
  M = adjugate(M);
  for (int s : {0, 1}) {
    for (int t : {0, 1}) {
      M[s][t] /= det;
    }
  }
  return M;
}

template <typename T>
std::vector<T> fwht(std::vector<T> v, Matrix<T> M) {
  int N = v.size();
  for (int len = 1; len < N; len *= 2) {
    for (int pos = 0; pos < N; pos += 2 * len) {
      for (int i = 0; i < len; ++i) {
        T x = v[pos + i], y = v[pos + len + i];
        v[pos + i] = M[0][0] * x + M[0][1] * y;
        v[pos + len + i] = M[1][0] * x + M[1][1] * y;
      }
    }
  }
  return v;
}

template <typename T>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b, Matrix<T> M) {
  auto ahat = fwht(a, M), bhat = fwht(b, M);
  int N = a.size();
  for (int i = 0; i < N; ++i) {
    ahat[i] *= bhat[i];
  }
  auto c = fwht(ahat, adjugate(M));
  T det = determinant(M), p = 1;
  for (int len = 1; len < N; len <<= 1) {
    p *= det;
  }
  for (int i = 0; i < N; ++i) {
    c[i] /= p;
  }
  return c;
}

template <typename T>
constexpr Matrix<T> or_matrix = {{{1, 0}, {1, 1}}};

template <typename T>
constexpr Matrix<T> and_matrix = {{{1, 1}, {0, 1}}};

template <typename T>
constexpr Matrix<T> xor_matrix = {{{+1, +1}, {+1, -1}}};

}  // namespace fwht

#endif  // ALGORITHMS_MATHEMATICS_FWHT_HPP

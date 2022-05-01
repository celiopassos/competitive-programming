#ifndef ALGORITHMS_MATHEMATICS_CHARACTERISTIC_POLYNOMIAL_HPP
#define ALGORITHMS_MATHEMATICS_CHARACTERISTIC_POLYNOMIAL_HPP

#include <algorithm>
#include <vector>

namespace characteristic_polynomial_auxiliary {

template <typename T>
std::vector<std::vector<T>> upper_hessenberg_form(std::vector<std::vector<T>> A) {
  int N = A.size();
  for (int i = 0; i + 2 < N; ++i) {
    int pivot = -1;
    for (int j = i + 1; j < N; ++j) {
      if (A[j][i] != 0) {
        pivot = j;
        break;
      }
    }
    if (pivot == -1) continue;
    std::swap(A[i + 1], A[pivot]);
    for (int j = 0; j < N; ++j) {
      std::swap(A[j][i + 1], A[j][pivot]);
    }
    for (int j = i + 2; j < N; ++j) {
      if (A[j][i] == 0) continue;
      T c = A[j][i] / A[i + 1][i];
      for (int k = i; k < N; ++k) {
        A[j][k] -= c * A[i + 1][k];
      }
      for (int k = 0; k < N; ++k) {
        A[k][i + 1] += c * A[k][j];
      }
    }
  }
  return A;
}

template <typename T>
T determinant_of_hessenberg(std::vector<std::vector<T>> A) {
  if (A.empty()) {
    return {1};
  }
  int N = A[0].size();
  T det = 1;
  for (int i = 0; i < N; ++i) {
    if (A[i][i] == 0) {
      det *= -1;
      if (i + 1 == N || A[i + 1][i] == 0) {
        return 0;
      }
      std::swap(A[i], A[i + 1]);
    }
    det *= A[i][i];
    if (i + 1 < N) {
      T c = A[i + 1][i] / A[i][i];
      for (int j = i; j < N; ++j) {
        A[i + 1][j] -= c * A[i][j];
      }
    }
  }
  return det;
}

template <typename T>
std::vector<T> convolution(const std::vector<T>& p, const std::vector<T>& q) {
  int N = p.size(), M = q.size();
  std::vector<T> r(N + M - 1);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      r[i + j] += p[i] * q[j];
    }
  }
  return r;
}

template <typename T>
std::vector<T> polynomial_interpolation(const std::vector<T>& y) {
  std::vector<T> p = {y[0]}, f = {1};
  for (int i = 1; i < y.size(); ++i) {
    T inv = T(1) / T(i);
    f = convolution({-(1 - inv), inv}, f);
    T v = y[i], pow = 1;
    for (auto a : p) {
      v -= a * pow;
      pow *= i;
    }
    p.push_back(0);
    for (int j = 0; j < p.size(); ++j) {
      p[j] += v * f[j];
    }
  }
  return p;
}

}  // namespace characteristic_polynomial_auxiliary

template <typename T>
std::vector<T> characteristic_polynomial(std::vector<std::vector<T>> A) {
  namespace aux = characteristic_polynomial_auxiliary;
  int N = A.size();
  A = aux::upper_hessenberg_form(std::move(A));
  std::vector<T> y(N + 1);
  for (int i = 0; i <= N; ++i) {
    T det = aux::determinant_of_hessenberg(A);
    y[i] = N % 2 ? -det : det;
    for (int j = 0; j < N; ++j) {
      A[j][j] -= 1;
    }
  }
  return aux::polynomial_interpolation(y);
}

#endif  // ALGORITHMS_MATHEMATICS_CHARACTERISTIC_POLYNOMIAL_HPP

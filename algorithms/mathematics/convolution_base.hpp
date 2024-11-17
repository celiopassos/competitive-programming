#ifndef ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP
#define ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP

#include <vector>

template <typename T>
struct Convolution {
  static std::vector<T> convolution(std::vector<T> p, std::vector<T> q) {
    int N = p.size(), M = q.size();
    std::vector<T> res(N + M - 1);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        res[i + j] += p[i] * q[j];
      }
    }
    return res;
  }
};

template <typename T>
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  return Convolution<T>::convolution(std::move(p), std::move(q));
}

#endif // ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP

#ifndef ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP
#define ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP

#include <vector>

template <typename T>
struct Convolution;

template <typename T>
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  return Convolution<T>::convolution(std::move(p), std::move(q));
}

#endif // ALGORITHMS_MATHEMATICS_CONVOLUTION_BASE_HPP

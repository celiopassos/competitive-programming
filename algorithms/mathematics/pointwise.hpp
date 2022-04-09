#ifndef ALGORITHMS_MATHEMATICS_POINTWISE_HPP
#define ALGORITHMS_MATHEMATICS_POINTWISE_HPP

#include "algorithms/common"

template <typename T, int K>
struct Pointwise : public std::array<T, K> {
  using P = Pointwise;
  Pointwise(T value = 0) {
    std::fill(this->begin(), this->end(), value);
  }
  P& operator+=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] += rhs[j];
    return *this;
  }
  P& operator-=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] -= rhs[j];
    return *this;
  }
  P& operator*=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] *= rhs[j];
    return *this;
  }
  P& operator/=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] /= rhs[j];
    return *this;
  }
  friend P operator+(P lhs, const P& rhs) {
    return lhs += rhs;
  }
  friend P operator-(P lhs, const P& rhs) {
    return lhs -= rhs;
  }
  friend P operator*(P lhs, const P& rhs) {
    return lhs *= rhs;
  }
  friend P operator/(P lhs, const P& rhs) {
    return lhs /= rhs;
  }
  P operator+() const {
    return *this;
  }
  P operator-() const {
    return P(T(0)) -= *this;
  }
};

#endif  // ALGORITHMS_MATHEMATICS_POINTWISE_HPP

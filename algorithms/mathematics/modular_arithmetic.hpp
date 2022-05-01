#ifndef ALGORITHMS_MATHEMATICS_MODULAR_ARITHMETIC_HPP
#define ALGORITHMS_MATHEMATICS_MODULAR_ARITHMETIC_HPP

#include <iostream>
#include <type_traits>

template <unsigned P>
struct Z {
  unsigned value;

  constexpr Z() : value(0) {}

  template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
  constexpr Z(T a) : value((((long long)a % P) + P) % P) {}

  Z& operator+=(Z rhs) {
    value += rhs.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator-=(Z rhs) {
    value += P - rhs.value;
    if (value >= P) value -= P;
    return *this;
  }

  Z& operator*=(Z rhs) {
    value = (unsigned long long)value * rhs.value % P;
    return *this;
  }

  Z& operator/=(Z rhs) {
    return *this *= pow(rhs, -1);
  }

  Z operator-() const {
    return Z() - *this;
  }

  bool operator==(Z rhs) const {
    return value == rhs.value;
  }

  bool operator!=(Z rhs) const {
    return value != rhs.value;
  }

  friend Z operator+(Z lhs, Z rhs) {
    return lhs += rhs;
  }

  friend Z operator-(Z lhs, Z rhs) {
    return lhs -= rhs;
  }

  friend Z operator*(Z lhs, Z rhs) {
    return lhs *= rhs;
  }

  friend Z operator/(Z lhs, Z rhs) {
    return lhs /= rhs;
  }

  friend std::ostream& operator<<(std::ostream& out, Z a) {
    return out << a.value;
  }

  friend std::istream& operator>>(std::istream& in, Z& a) {
    long long value;
    in >> value;
    a = Z(value);
    return in;
  }
};

template <unsigned P>
Z<P> pow(Z<P> x, long long p) {
  p %= P - 1;
  if (p < 0) p += P - 1;
  Z<P> res = 1;
  while (p) {
    if (p & 1) {
      res *= x;
    }
    x *= x;
    p >>= 1;
  }
  return res;
}

#endif  // ALGORITHMS_MATHEMATICS_MODULAR_ARITHMETIC_HPP

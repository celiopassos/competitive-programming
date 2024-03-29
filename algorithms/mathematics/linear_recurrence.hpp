#ifndef ALGORITHMS_MATHEMATICS_LINEAR_RECURRENCE_HPP
#define ALGORITHMS_MATHEMATICS_LINEAR_RECURRENCE_HPP

#include <vector>

template <typename T>
T one_coeff(std::vector<T> p, std::vector<T> q, long long n) {
  int d = p.size();
  for (; n > 0; n >>= 1) {
    auto qsgn = q;
    for (int i = 1; i <= d; i += 2) {
      qsgn[i] *= -1;
    }
    auto u = p * qsgn, v = q * qsgn;
    int b = n & 1;
    for (int i = 0; i < d; ++i) {
      p[i] = u[i << 1 | b];
      q[i] = v[i << 1];
    }
    q[d] = v[d << 1];
  }
  return p[0] / q[0];
}

// Given the linear recurrence u[i+1] = c[0]u[i] + ... + c[d-1]u[i - (d - 1)] and the initial values u[0], ..., u[d-1],
// finds u[n].
// Time complexity: O(convolution(d) * log(n)).
template <typename T>
T solve_linear_recurrence(std::vector<T> c, std::vector<T> u, long long n) {
  assert(c.size() <= u.size());
  if (n < u.size()) {
    return u[n];
  } else if (c.empty()) {
    return 0;
  }
  u.resize(c.size());
  int d = c.size(); 
  std::vector<T> q(d + 1, 0);
  q[0] = 1;
  for (int i = 0; i < d; ++i) q[i + 1] -= c[i];
  auto p = u * q;
  p.resize(d);
  return one_coeff(p, q, n);
}

#endif  // ALGORITHMS_MATHEMATICS_LINEAR_RECURRENCE_HPP

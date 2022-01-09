template <typename T>
T one_coeff(std::vector<T> p, std::vector<T> q, int64_t n) {
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
// given the linear recurrence u[i+d] = c[0]u[i] + ... + c[d-1]u[i+d-1]
// and the initial values u[0], ..., u[d-1], finds u[n]
// O(convolution(d) * log(n))
template <typename T>
T solve_linear_recurrence(std::vector<T> c, std::vector<T> u, int64_t n) {
  int d = c.size();
  std::vector<T> q(d + 1, 0);
  q[0] = 1;
  for (int i = 0; i < d; ++i) q[d - i] -= c[i];
  auto p = u * q;
  p.resize(d);
  return one_coeff(p, q, n);
}

#ifndef ALGORITHMS_MATHEMATICS_DISCRETE_LOG_HPP
#define ALGORITHMS_MATHEMATICS_DISCRETE_LOG_HPP

#include "algorithms/common"

#include <cmath>
#include <unordered_map>

// Returns minimum x such that a^x = b (-1 if there is none).
// Time complexity: O(sqrt(mod)).
long long discrete_log(long long a, long long b, long long mod) {
  assert(0 <= a < mod);
  assert(0 <= b < mod);
  long long k = 1, add = 0;
  while (true) {
    long long g = std::gcd(a, mod);
    if (g == 1) break;
    if (b == k) return add;
    if (b % g) return -1;
    b /= g;
    mod /= g;
    k = k * a / g % mod;
    ++add;
  }
  long long d = 1 + sqrtl(mod);
  std::unordered_map<long long, int> small;
  long long x = 1;
  for (int i = 1; i <= d; ++i) {
    x = x * a % mod;
    small[b * x % mod] = i;
  }
  long long y = k;
  for (int i = 1; i <= d; ++i) {
    y = y * x % mod;
    if (small.count(y)) {
      return i * d - small[y] + add;
    }
  }
  return -1;
}

#endif  // ALGORITHMS_MATHEMATICS_DISCRETE_LOG_HPP

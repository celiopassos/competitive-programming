#ifndef ALGORITHMS_MATHEMATICS_SIEVE_HPP
#define ALGORITHMS_MATHEMATICS_SIEVE_HPP

#include "algorithms/common"

struct Sieve {
  struct PrimePower {
    int p = -1, pow, k;  // pow = p^k
  };

  std::vector<PrimePower> lp;
  std::vector<int> primes;

  Sieve(int N) : lp(N + 1) {
    for (int i = 2; i <= N; ++i) {
      if (lp[i].p == -1) {
        lp[i].p = lp[i].pow = i;
        lp[i].k = 1;
        primes.push_back(i);
      }
      for (auto p : primes) {
        if (i * p > N || p > lp[i].p) break;
        int j = i * p;
        lp[j].p = p;
        if (p == lp[i].p) {
          lp[j].pow = p * lp[i].pow;
          lp[j].k = lp[i].k + 1;
        } else {
          lp[j].pow = p;
          lp[j].k = 1;
        }
      }
    }
  }

  const PrimePower& operator[](int i) const {
    return lp[i];
  }
};

#endif  // ALGORITHMS_MATHEMATICS_SIEVE_HPP
